/*@ inductive factorial_ind(integer i, integer f) {
    case nil:
       factorial_ind(0, 1);
    case step_inc:
       \forall integer i, f;
          factorial_ind(i - 1, f) ==> factorial_ind(i, f * i);
    }

    lemma factorial_ind_20:
       factorial_ind(20, 2432902008176640000);
    lemma increasing:
       \forall integer i1, i2, f1, f2;
          i2 >= i1 && factorial_ind(i1, f1) && factorial_ind(i2, f2) ==> f2 >= f1;
 */

#define SPEC_ULONG_MAX 18446744073709551615UL

/*@ requires i <= 20;
    decreases i;
    assigns \nothing;
    ensures factorial_ind(i, \result);
 */
unsigned long factorial_rec(unsigned i)
{
   if (i == 0) {
      return 1;
   } else {
      return factorial_rec(i - 1) * i;
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   printf("res: %lu\n", factorial_rec(10));
   printf("res: %lu\n", factorial_rec(20));
   return 0;
}
#endif
