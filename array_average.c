/*@ axiomatic ASum {
    logic integer asum{L}(int *a, integer b);

    axiom asum_init{L}:
       \forall int *a, integer b; b <= 0 ==> asum(a, b) == 0;

    axiom asum_step_dec{L}:
       \forall int *a, integer b; asum(a, b) == asum(a, b-1) + a[b];
    }
 */

#define SPEC_INT_MIN -2147483648
#define SPEC_INT_MAX 2147483647


/*@ requires size > 0; // Найти ошибку
    requires \valid(a+(0..size-1));
    requires SPEC_INT_MIN <= asum(a, size-1) <= SPEC_INT_MAX;
    assigns \nothing;
    ensures \result == (asum(a, size-1) / size);
 */
int array_average(int a[], int size)
{
   int i;
   int sum = 0;

   /*@ loop invariant 0 <= i <= size;
       loop invariant sum == asum(a, i-1);
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      sum += a[i];
   }

   return sum / size;
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   int a[] = {1,2,3,4,5,6,7,8,9,10};
   int size = sizeof(a) / sizeof(a[0]);
   
   printf("res: %d\n", array_average(a, size));
   
   return 0;
}
#endif
