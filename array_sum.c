/*@ axiomatic Sum {
    logic integer sum{L}(unsigned *a, integer b);

    axiom init{L}:
       \forall unsigned *a, integer b; b <= 0 ==> sum(a, b) == 0;

    axiom step_dec{L}:
       \forall unsigned *a, integer b; sum(a, b) == sum(a, b-1) + a[b];

    lemma lower_bound:
       \forall unsigned *a, integer b; sum(a, b) >= 0;

    lemma sum_increases:
       \forall unsigned *a, integer i, b; 0 <= i <= b ==> sum(a, i) <= sum(a, b);
    }
 */

#define UINT_MAX 32767

/*@ requires \valid(a+(0..n-1));
    requires sum(a, n) < UINT_MAX;
    assigns \nothing;
    ensures \result == sum(a, n-1);
 */
unsigned array_sum(unsigned a[], unsigned n)
{
   unsigned i;
   unsigned sum = 0;

   /*@ loop invariant 0 <= i <= n;
       loop invariant sum == sum(a, i-1);
       //loop invariant sum(a, i-1) < UINT_MAX; Не обязательно
       loop variant n - i;
    */
   for(i = 0; i < n; ++i) {
      sum += a[i];
   }

   return sum;
}
