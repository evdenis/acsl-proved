/*@ axiomatic Factorial {
    logic integer factorial(integer i);
    axiom nil:
       factorial(0) == 1;
    axiom step:
       \forall integer i; i >= 0 ==>
          factorial(i) == factorial(i - 1) * i;

    lemma non_negative:
       \forall integer i; i >= 0 ==>
          factorial(i) > 0;
    }
 */

#define SPEC_ULONG_MAX 18446744073709551615UL

/*@ requires factorial(i) <= SPEC_ULONG_MAX;
    assigns \nothing;
    ensures \result == factorial(i);
 */
unsigned long factorial(unsigned i)
{
   unsigned long f = 1;
   /*@ loop invariant 0 <= i;
       loop assigns f, i;
       loop variant i;
    */
   while (i) {
      f *= i--;
   }
   return f;
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   printf("res: %lu\n", factorial(10));
   printf("res: %lu\n", factorial(20));
   return 0;
}
#endif
