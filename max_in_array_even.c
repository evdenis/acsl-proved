#define INT_MAX 2147483647

/* lemma odd_even:
       \forall integer i; (i >= 0) ==> (i % 2 == 0) || (i % 2 == 1);
    lemma odd_next:
       \forall integer i; (i >= 0) && (i % 2 == 0) ==> ((i + 1) % 2) == 1;
    lemma even_next:
       \forall integer i; (i >= 0) && (i % 2 == 1) ==> ((i + 1) % 2) == 0;
 */

/*@ requires size > 0;
    requires size <= INT_MAX - 1;
    requires \valid(a + (0..size - 1));
    ensures 0 <= \result < size;
    ensures \result % 2 == 0;
    ensures \forall integer i; (0 <= i < size) && (i % 2 == 0) ==> a[i] <= a[\result];
 */
int max_in_array_even(int *a, int size)
{
   int j = 0;
   int max = a[0];

   /*@ loop invariant 2 <= i <= size + 1;
       loop invariant 0 <= j < i;
       loop invariant i % 2 == 0 && j % 2 == 0;
       loop invariant max == a[j];
       loop invariant \forall integer k; (0 <= k < i) && (k % 2 == 0) ==> a[k] <= max;
       loop variant size - i;
    */
   for(int i = 2; i < size; i += 2) {
      if (max < a[i]) {
         j = i;
         max = a[i];
      }
   }

   return j;
}

#ifdef OUT_OF_TASK

#include <stdio.h> 

int main(int argc, char **argv)
{
   int max1[] = {1, 2, 3, 4, 5, -1, -10, 6, 32, 101};
   int max2[] = {-1, 0, -3, 0, -5, 0, -10, 0, -32};
   int res1 = max_in_array_even(max1, sizeof(max1)/sizeof(int));
   int res2 = max_in_array_even(max2, sizeof(max2)/sizeof(int));
   printf("max1: %d\n", max1[res1]);
   printf("max2: %d\n", max2[res2]);
   return 0;
}

#endif
