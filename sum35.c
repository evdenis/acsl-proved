#define UINT_MAX 4294967295

/*@ axiomatic Sum35 {
    logic integer sum35(integer b);

    axiom sum35_negative:
       \forall integer i; i <= 0 ==> sum35(i) == 0;

    axiom sum35_iter1:
       \forall integer b; b >= 0 && (((b + 1) % 3 != 0) && ((b + 1) % 5 != 0)) ==>
          sum35(b + 1) == sum35(b);

    axiom sum35_iter2:
       \forall integer b; b >= 0 && (((b + 1) % 3 == 0) || ((b + 1) % 5 == 0)) ==>
          sum35(b + 1) == sum35(b) + (b + 1);

    lemma sum35_lower_bound:
       \forall integer bound; bound >= 0 ==> sum35(0) >= 0;

    lemma sum35_increases:
       \forall integer b1, b2; 0 <= b1 <= b2 ==> sum35(b1) <= sum35(b2);
    }
 */


/*@ requires bound <= 10;
    assigns \nothing;
    ensures \result == sum35(bound - 1);
 */
unsigned calc(unsigned bound)
{
   unsigned sum = 0;

   /*@ loop invariant (bound != 0) ==> 1 <= i <= bound;
       loop invariant (bound == 0) ==> (i == 1 && sum == 0);
       loop invariant sum <= UINT_MAX;
       loop invariant sum == sum35(i - 1);
       loop assigns i, sum;
       loop variant bound - i;
    */
   for(unsigned i = 1; i < bound; ++i) {
      if (!(i % 3) || !(i % 5)) {
         sum += i;
      }
   }

   return sum;
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(int argc, char **argv)
{
   printf("%u\n", calc(0));
   printf("%u\n", calc(10));
   printf("%u\n", calc(100));
   printf("%u\n", calc(1000));
   return 0;
}

#endif
