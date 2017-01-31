/*@ requires \valid(a+(0..size-1));
    requires \valid(max);
    requires \valid(min);
    behavior zero_size:
       assumes size == 0;
       assigns \nothing;
       ensures max == \old(max) && min == \old(min);
    behavior one_size:
       assumes size == 1;
       assigns *max, *min;
       ensures *max == a;
       ensures *max == *min;
       ensures **max == **min;
    behavior size:
       assumes size > 1;
       assigns *max, *min;
       ensures \exists integer i; 0 <= i < size && (a + i) == *max;
       ensures \exists integer i; 0 <= i < size && (a + i) == *min;
       ensures **max >= **min;
       ensures \forall integer i; 0 <= i < size ==> **max >= a[i] >= **min;
    complete behaviors;
    disjoint behaviors;
 */
void max_min(int a[], unsigned size, int **max, int **min)
{
   if (size > 0) {
      unsigned i;
      *max = &a[0];
      *min = *max;
      /*@ loop invariant 1 <= i <= size;
          loop invariant \exists integer j; 0 <= j < i && (a+j) == *max;
          loop invariant \exists integer j; 0 <= j < i && (a+j) == *min;
          loop invariant **max >= **min;
          loop invariant \forall integer j; 0 <= j < i ==> **max >= a[j] >= **min;
          loop assigns *max, *min;
          loop variant size - i;
       */
      for(i = 1; i < size; ++i) {
         if (**max < a[i]) {
            *max = &a[i];
         } else if (**min > a[i]) {
            *min = &a[i];
         }
      }
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>
int main(void)
{
   int a[] = {3,5,3,1,5,11,7,8,9,10};
   int *max, *min;
   max_min(a, sizeof(a)/sizeof(a[0]), &max, &min);
   printf("max: el: %ld val: %d; min: el: %ld val: %d\n", max - a, *max, min - a, *min);
   return 0;
}
#endif
