/*@ requires \valid(&a[i]);
    requires \valid(&a[j]);
    assigns a[i], a[j];
    ensures a[i] == \old(a[j]);
    ensures a[j] == \old(a[i]);
 */
void swap(int a[], int i, int j)
#ifndef OUT_OF_TASK
;
#else
{
   int tmp = a[i];
   a[i] = a[j];
   a[j] = tmp;
}
#endif

/*@ predicate reverse{L1,L2}(int* a, integer size, integer i, integer j) =
       \forall integer k; i <= k < j ==>
          \at(a[k], L1) == \at(a[size - k - 1], L2);
    predicate reverse{L1,L2}(int* a, integer size) = reverse{L1,L2}(a, size, 0, size);
*/

/*@ requires size >= 0;
    requires \valid(a+(0..size-1));
    assigns a[0..size-1];
    ensures reverse{Pre,Here}(a, size);
    ensures \forall integer i; 0 <= i < size ==>
            \exists integer j; 0 <= j < size &&
            a[i] == a[j];
 */
void reverse_in_place(int a[], int size)
{
   int i;
   /*@ loop invariant 0 <= i <= size / 2;
       loop invariant reverse{Pre,Here}(a, size, 0, i);
       loop invariant \forall integer j; i <= j < size - i ==> a[j] == \at(a[\at(j,Here)],Pre);
       loop invariant reverse{Pre,Here}(a, size, size - i, size);
       loop assigns i, a[0..size-1];
       loop variant size / 2 - i;
    */
   for(i = 0; i < (size / 2); ++i) {
      swap(a, i, size - i - 1);
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   int a[] = {1,2,3,4,5,6,7,8,9,10};
   int size = sizeof(a) / sizeof(a[0]);
   for(int i = 0; i < size; ++i) {
      printf("%d ", a[i]);
   }
   printf("\n");
   reverse_in_place(a, size);
   for(int i = 0; i < size; ++i) {
      printf("%d ", a[i]);
   }
   printf("\n");
}
#endif
