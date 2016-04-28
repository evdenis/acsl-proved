/*@ requires \valid(a+(0..size-1));
    requires \valid(max1) && \valid(max2);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures max1 == \old(max1);
       ensures max2 == \old(max2);
    behavior positive_size:
       assumes size > 0;
       assigns *max1, *max2;
       ensures \valid(max1) && \valid(max2);
       ensures \exists integer i; 0 <= i < size && (a + i) == *max1;
       ensures \exists integer i; 0 <= i < size && (a + i) == *max2;
       ensures **max1 >= **max2;
       ensures \forall integer i; 0 <= i < size ==> a[i] <= **max1;
       ensures \exists integer i; 0 <= i < size && a[i] >= **max2 && a[i] == **max1;
       ensures ! \exists integer i,j; 0 <= i < size && 0 <= j < size && i != j && (a[i] > **max2 && a[j] > **max2);
    complete behaviors;
    disjoint behaviors;
 */
void max_max(int *a, unsigned size, int **max1, int **max2)
{

   if (size > 0) {
      //int i; Найдите ошибку
      unsigned i;
      *max1 = &a[0];
      *max2 = *max1;
      //@ assert *max1 == a;
      //@ assert *max2 == a;

      /*@ loop invariant 0 < i <= size;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *max1;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *max2;
          loop invariant **max1 >= **max2;
          loop invariant \forall integer j; 0 <= j < i ==> a[j] <= **max1;
          loop invariant \exists integer j; 0 <= j < i && a[j] > **max2 && a[j] == **max1;
          loop assigns *max1, *max2;
          loop variant size - i;
       */
      for(i = 1; i < size; ++i) {
         if (a[i] > **max1) {
            *max2 = *max1;
            *max1 = &a[i];
         } else if (a[i] > **max2) {
            *max2 = &a[i];
         }
      }
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>
int main(void)
{
   int a[] = {1,2,3,4,5,11,7,8,9,10};
   int *max1, *max2;
   max_max(a, sizeof(a)/sizeof(a[0]), &max1, &max2);
   printf("max1: el: %d val: %d; max2: el: %d val: %d\n", max1 - a, *max1, max2 - a, *max2);
   return 0;
}
#endif
