/*@ axiomatic Power {
    logic integer power_int_pos(integer b, integer p);
    axiom power_nil:
       \forall integer b;
          power_int_pos(b, 0) == 1;
    axiom power_step:
       \forall integer b, p; p >= 0 ==>
          power_int_pos(b, p + 1) == b * power_int_pos(b, p);
    lemma power_alt_step:
       \forall integer b, p; p > 0 ==>
          power_int_pos(b, p) == b * power_int_pos(b, p - 1);
    lemma power_one:
       \forall integer b;
          power_int_pos(b, 1) == b;
    lemma power_sum:
       \forall integer b, p1, p2; p1 >= 0 && p2 >= 0 ==>
          power_int_pos(b, p1 + p2) == power_int_pos(b, p1) * power_int_pos(b, p2);
    lemma power_mult_1:
       \forall integer b, p1, p2; p1 >= 0 && p2 >= 0 ==>
          power_int_pos(b, p1 * p2) == power_int_pos(power_int_pos(b, p1), p2);
    lemma power_mult_2: 
       \forall integer b1, b2, p; p >= 0 ==>
          power_int_pos(b1 * b2, p) == power_int_pos(b1, p) * power_int_pos(b2, p);
    lemma power_non_negative:
       \forall integer b, p; b >= 0 && p >= 0 ==> power_int_pos(b, p) >= 0;
    lemma power_monotonic:
       \forall integer b, p1, p2; b > 0 && 0 <= p1 <= p2 ==> power_int_pos(b, p1) <= power_int_pos(b, p2);
    }
 */

/*@ axiomatic Fib {
    logic integer fib(integer i);
    axiom fib_nil:
       fib(0) == 0;
    axiom fib_one:
       fib(1) == 1;
    axiom fib_step_positive:
       \forall integer i; i >= 2 ==>
          fib(i) == fib(i - 1) + fib(i - 2);
    axiom fib_step_negative:
       \forall integer i; i < 0 ==>
          fib(i) == fib(i + 2) - fib(i + 1);
    lemma fib_non_negative:
       \forall integer i; i >= 0 ==>
          fib(i) >= 0;
    lemma fib_non_negative_increasing:
       \forall integer i, j; i >= 0 && j >= 0 && i >= j ==>
          fib(i) >= fib(j);
    lemma fib_negative_positive_1:
       \forall integer i; i < 0 ==>
          fib(i) == power_int_pos(-1, i + 1) * fib(-i);
    lemma fib_negative_positive_2:
       \forall integer i; i < 0 ==>
          \abs(fib(i)) == fib(-i);
    }
 */

#define INT_MAX 2147483647
#define INT_MIN -2147483648

/*@ requires INT_MIN <= fib(i) <= INT_MAX;
    assigns \nothing;
    ensures \result == fib(i);
 */
int fib(int i)
{
   int sign_i = i == 0 ? 0 : (i > 0 ? 1 : -1);
   // assert sign_i == \sign(i);
   unsigned abs_i = sign_i * i;
   //@ assert abs_i == \abs(i);
   int a[abs_i + 2];
   a[0] = 0; a[1] = sign_i * 1;

   unsigned j;
   int fsign = sign_i;
   /*@ loop invariant 2 <= j <= abs_i + 2;
       loop invariant \forall integer k; 0 <= k < j ==> a[k] == fib(k);
       loop assigns a[2..abs_i];
       loop variant abs_i - j;
    */
   for(j = 2; j <= abs_i; ++j) {
      fsign *= sign_i;
      a[j] = (a[j - 1] + a[j - 2]);
   }

   return fsign * a[abs_i];
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   for(int i = -15; i <= 15; ++i) {
      printf("%d\n", fib(i));
   }
   return 0;
}
#endif
