/*@ requires size >= 2;
    requires \valid(a + (0..size-1));
    requires \valid(max);
    requires \valid(min);
    requires max != min;
    assigns *max, *min;
    ensures 0 <= *max < size;
    ensures 0 <= *min < size;
    behavior max:
       ensures \forall integer i; (0 <= i < size) && (i % 2 == 0) ==> a[i] <= a[*max];
    behavior min:
       ensures \forall integer i; (0 <= i < size) && (i % 2 == 1) ==> a[*min] <= a[i];
*/
void max_min_in_array_odd_even(int *a, int size, int *max, int *min)
{
   int mx = 0;
   int mn = 1;

   /*@ loop invariant 2 <= i <= size;
       loop invariant 0 <= mx < size;
       loop invariant 1 <= mn < size;
       for max: loop invariant \forall integer j; (0 <= j < i) && (j % 2 == 0) ==> a[j] <= a[mx];
       for min: loop invariant \forall integer j; (0 <= j < i) && (j % 2 == 1) ==> a[mn] <= a[j];
       loop variant size - i;
    */
   for(int i = 2; i < size; ++i) {
      if (i % 2) {
         if (a[mn] > a[i]) mn = i;
      } else {
         if (a[mx] < a[i]) mx = i;
      }
   }

   *max = mx;
   *min = mn;
}

#ifdef OUT_OF_TASK
#include <stdio.h>
int main(void)
{
   int a[] = {3,5,3,1,5,11,7,8,9,10};
   int max, min;
   max_min_in_array_odd_even(a, sizeof(a)/sizeof(a[0]), &max, &min);
   printf("max: %d; min: %d\n", max, min);
   return 0;
}
#endif
