/*@ predicate is_divisor(integer m, integer n) =
       (m != 0) ==> n % m == 0;
*/

/*@ predicate is_gcd(integer z, integer x1, integer x2) =
	   is_divisor(z, x1)
	&& is_divisor(z, x2)
	&& \forall integer i; is_divisor(i, x1) && is_divisor(i, x2) ==> (i <= z);
 */

/*@ axiomatic gcd {
       logic integer gcd(integer a, integer b);

       axiom nil:
          \forall integer n; gcd(n,0) == n;
       axiom next:
          \forall integer a, b; gcd(b, a % b) == gcd(a,b);

       lemma gcd_def:
          \forall integer a, b; is_gcd(gcd(a, b), a, b);
    }
 */


/*@ requires x1 > 0 && x2 > 0;
    assigns \nothing;
    ensures is_gcd(\result, x1, x2);
 */
unsigned gcd(unsigned x1, unsigned x2)
{
	unsigned y1 = x1;
	unsigned y2 = x2;
	unsigned tmp = 0;

	if (y1 > y2) {
		y1 = x2;
		y2 = x1;
	}
   //@ assert y1 == \min(x1, x2);
   //@ assert y2 == \max(x1, x2);

   /*@ loop invariant 0 <= y1 <= y2;
       loop invariant y2 > 0;
       loop invariant (y1 > 0)  ==> gcd(x1, x2) == gcd(y1, y2);
       loop invariant (y1 == 0) ==> gcd(x1, x2) == y2;
       loop variant y1;
	 */
	while (y1 != 0) {
		tmp = y1;
		y1 = y2 % y1;
		y2 = tmp;
	}

   return y2;
}

/*@ requires x1 > 0;
    decreases x2;
    assigns \nothing;
    ensures is_gcd(\result, x1, x2);
    ensures \result == gcd(x1, x2);
 */
unsigned gcd_rec(unsigned x1, unsigned x2)
{
   if (x2 == 0)
      return x1;

   return gcd_rec(x2, x1 % x2);
}

/*@ requires x1 > 0 && x2 > 0;
    assigns \nothing;
    ensures is_gcd(\result, x1, x2);
 */
unsigned gcd_raw(unsigned x1, unsigned x2)
{
   unsigned min = x1 > x2 ? x2 : x1;
   //@ assert min == \min(x1, x2);
   unsigned gcd = 1;

   /*@ loop invariant 2 <= i <= min + 1;
       loop invariant 1 <= gcd < i;
       loop invariant is_divisor(gcd, x1);
       loop invariant is_divisor(gcd, x2);
       loop invariant \forall integer j; 0 <= j < i && is_divisor(j, x1) && is_divisor(j, x2) ==> (j <= gcd);
       loop invariant gcd <= gcd(x1, x2);
       loop assigns gcd;
       loop variant min - i;
    */
   for(unsigned i = 2; i <= min; ++i) {
      if (x1 % i == 0 && x2 % i == 0) {
         gcd = i;
      }
   }

   return gcd;
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(int argc, char **argv)
{
   for(int i = 1; i < 1000; ++i) {
      for(int j = 1; j < 1000; ++j) {
         int res1 = gcd(i, j);
         int res2 = gcd_rec(i, j);
         int res3 = gcd_raw(i, j);
         if (res1 != res2 || res2 != res3) {
            printf("i: %d, j: %d, res1: %d, res2: %d, res3: %d\n", i, j, res1, res2, res3);
         }
      }
   }
   return 0;
}
#endif
