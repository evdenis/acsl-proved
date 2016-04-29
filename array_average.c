/*@ axiomatic Sum {
    logic integer sum{L}(int *a, integer b);

    axiom init{L}:
       \forall int *a, integer b; b <= 0 ==> sum(a, b) == 0;

    axiom step_dec{L}:
       \forall int *a, integer b; sum(a, b) == sum(a, b-1) + a[b];
    }
 */

#define INT_MIN -2147483648
#define INT_MAX 2147483647


/*@ requires size > 0; // Найти ошибку
    requires \valid(a+(0..size-1));
    requires INT_MIN <= sum(a, size-1) <= INT_MAX;
    assigns \nothing;
    ensures \result == (sum(a, size-1) / size);
 */
int array_average(int a[], int size)
{
   int i;
   int sum = 0;

   /*@ loop invariant 0 <= i <= size;
       loop invariant sum == sum(a, i-1);
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      sum += a[i];
   }

   return sum / size;
}
