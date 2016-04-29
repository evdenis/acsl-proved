/*@ requires \valid(a+(0..size-1));
    requires \valid(min1) && \valid(min2);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures min1 == \old(min1);
       ensures min2 == \old(min2);
    behavior positive_size:
       assumes size > 0;
       assigns *min1, *min2;
       ensures \valid(min1) && \valid(min2);
       ensures \exists integer i; 0 <= i < size && (a + i) == *min1;
       ensures \exists integer i; 0 <= i < size && (a + i) == *min2;
       ensures **min1 <= **min2;
       ensures \forall integer i; 0 <= i < size ==> a[i] >= **min1;
       ensures \exists integer i; 0 <= i < size && a[i] <= **min2 && a[i] == **min1;
       ensures ! (\exists integer i,j; 0 <= i < size && 0 <= j < size && i != j && (a[i] < **min2 && a[j] < **min2 && a[i] < a[j]));
    complete behaviors;
    disjoint behaviors;
 */
void min_min(int *a, unsigned size, int **min1, int **min2)
{

   if (size > 0) {
      //int i; Найдите ошибку
      unsigned i;
      *min1 = &a[0];
      *min2 = *min1;

      /*@ loop invariant 0 < i <= size;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *min1;
          loop invariant \exists integer j; 0 <= j < i && (a + j) == *min2;
          loop invariant **min1 <= **min2;
          loop invariant \forall integer j; 0 <= j < i ==> a[j] >= **min1;
          loop invariant \exists integer j; 0 <= j < i && a[j] <= **min2 && a[j] == **min1;
          loop invariant ! (\exists integer j,k; 0 <= j < i && 0 <= k < i && j != k && (a[j] < **min2 && a[k] < **min2 && a[k] < a[j]));
          loop assigns *min1, *min2;
          loop variant size - i;
       */
      for(i = 1; i < size; ++i) {
         if (a[i] < **min1) {
            *min2 = *min1;
            *min1 = &a[i];
         } else if (a[i] < **min2) {
            *min2 = &a[i];
         }
      }
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>
int main(void)
{
   int a[] = {1,2,3,4,5,11,7,8,9,10};
   int *min1, *min2;
   min_min(a, sizeof(a)/sizeof(a[0]), &min1, &min2);
   printf("min1: el: %d val: %d; min2: el: %d val: %d\n", min1 - a, *min1, min2 - a, *min2);
   return 0;
}
#endif
