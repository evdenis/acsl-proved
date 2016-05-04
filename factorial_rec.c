/*@ inductive factorial(integer i, integer f) {
    case nil:
       factorial(0, 1);
    case step_inc:
       \forall integer i, f;
          factorial(i - 1, f) ==> factorial(i, f * i);
    }

    lemma factorial_20:
       factorial(20, 2432902008176640000);
    lemma increasing:
       \forall integer i1, i2, f1, f2;
          i2 >= i1 && factorial(i1, f1) && factorial(i2, f2) ==> f2 >= f1;
 */

#define ULONG_MAX 18446744073709551615UL

/*@ requires i <= 20;
    decreases i;
    assigns \nothing;
    ensures factorial(i, \result);
 */
unsigned long factorial_rec(unsigned i)
{
   if (i == 0) {
      return 1;
   } else {
      return factorial_rec(i - 1) * i;
   }
}
