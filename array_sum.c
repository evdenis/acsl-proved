/*@ axiomatic Array_Sum {
    logic integer array_sum{L}(unsigned *a, integer b);

    axiom array_sum_init{L}:
       \forall unsigned *a, integer b; b <= 0 ==> array_sum(a, b) == 0;

    axiom array_sum_step_dec{L}:
       \forall unsigned *a, integer b; array_sum(a, b) == array_sum(a, b-1) + a[b];

    lemma array_sum_lower_bound:
       \forall unsigned *a, integer b; array_sum(a, b) >= 0;

    lemma array_sum_increases:
       \forall unsigned *a, integer i, b; 0 <= i <= b ==> array_sum(a, i) <= array_sum(a, b);
    }
 */

#define UINT_MAX 32767

/*@ requires \valid(a+(0..n-1));
    requires array_sum(a, n) < UINT_MAX;
    assigns \nothing;
    ensures \result == array_sum(a, n-1);
 */
unsigned array_sum(unsigned a[], unsigned n)
{
   unsigned i;
   unsigned sum = 0;

   /*@ loop invariant 0 <= i <= n;
       loop invariant sum == array_sum(a, i-1);
       //loop invariant array_sum(a, i-1) < UINT_MAX; Не обязательно
       loop variant n - i;
    */
   for(i = 0; i < n; ++i) {
      sum += a[i];
   }

   return sum;
}
