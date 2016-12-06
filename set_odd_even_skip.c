
/*@ requires \valid(a+(0..n-1));
    assigns a[0..n-1];
    ensures \forall integer i; 0 <= i < n && (i % 2 == 0) && (i % 3 != 0) ==> a[i] == 1;
    ensures \forall integer i; 0 <= i < n && (i % 2 == 1) && (i % 3 != 0) ==> a[i] == 0;
    ensures \forall integer i; 0 <= i < n && (i % 3 == 0) ==> a[i] == \old(a[i]);
 */
void set_odd_even_skip(int a[], unsigned n)
{
   unsigned i;
   /*@ loop invariant 0 <= i <= n;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 0 && j % 3 != 0 ==> a[j] == 1;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 1 && j % 3 != 0 ==> a[j] == 0;
       loop invariant \forall integer j; 0 <= j < i && j % 3 == 0 ==> a[j] == \at(a[\at(j,Here)], Pre);
       loop assigns a[0..i-1];
       loop variant n - i;
    */
   for(i = 0; i < n; ++i) {
      if (i % 3 == 0) {
         continue;
      } else if (i % 2 == 0) {
         a[i] = 1;
      } else {
         a[i] = 0;
      }
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>

void print_int_array(int a[], int size)
{
   for(int i = 0; i < size - 1; ++i) {
      printf("%d, ", a[i]);
   }
   printf("%d", a[size - 1]);
}

int main(void)
{
   int a[] = {1,2,3,4,5,6,7,8,9,10};
   int size = sizeof(a) / sizeof(a[0]);
   
   printf("orig: ");
   print_int_array(a, size);
   printf("\n");
   
   set_odd_even_skip(a, size);
   
   printf("res: ");
   print_int_array(a, size);
   printf("\n");
   
   return 0;
}
#endif
