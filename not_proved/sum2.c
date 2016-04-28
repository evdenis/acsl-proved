#define INT_MIN -2147483648
#define INT_MAX 2147483647

/*@ assigns \nothing;
    ensures \result == \abs(x);
 */
unsigned abs(int x);

/*@ axiomatic Sum2 {
    logic integer sum2(integer a, integer b);

    axiom init:
       \forall integer a, b; (a >= 0 && b >= 0) && b <= a ==> sum2(a, b) == a;

    axiom step_dec:
       \forall integer a, b; (a >= 0 && b >= 0) && b > a ==> sum2(a, b) == sum2(a, b - 1) + b;

    lemma lower_bound:
       \forall integer a, b; a >= 0 && b >= 0 ==> sum2(a, b) >= a;

    lemma sum_increases:
       \forall integer i, a, b; (a >= 0 && b >= 0) && b > a && a <= i <= b ==> sum2(a, i) <= sum2(a, b);
    }
 */


/*@ requires x*x <= INT_MAX;
    assigns \nothing;
    ensures x >= 0;
    ensures
 */
int sum2(int x)
{
   int sum = x * x;
   x = abs(x);
   /*@ loop invariant 0 <= x;
       loop variant x;
    */
   while (x--) {
      sum += x * x;
   }
   return sum;
}
