/*@ axiomatic Sum {
    logic integer sum(integer a, integer b);

    axiom sum_init:
       \forall integer a, b; (a >= 0 && b >= 0) && b <= a ==> sum(a, b) == a;

    axiom sum_step_dec:
       \forall integer a, b; (a >= 0 && b >= 0) && b > a ==> sum(a, b) == sum(a, b - 1) + b;

    lemma sum_lower_bound:
       \forall integer a, b; a >= 0 && b >= 0 ==> sum(a, b) >= a;

    lemma sum_increases:
       \forall integer i, a, b; (a >= 0 && b >= 0) && b > a && a <= i <= b ==> sum(a, i) <= sum(a, b);
    }
 */

#define INT_MAX 32767

/*@ requires a < b;
    requires a >= 0 && b >= 0;
    requires sum(a, b) < INT_MAX;
    assigns \nothing;
    ensures \result == sum(a, b);
 */
int sum(int a, int b)
{
   int i;
   int sum = a;

   /*@ loop invariant a < i <= (b+1);
       loop invariant sum == sum(a, i - 1);
       //loop invariant sum(a, i - 1) < INT_MAX; Доказывается и без него
       loop variant b - i;
    */
   for(i = a + 1; i <= b; ++i) {
      sum += i;
   }

   return sum;
}
