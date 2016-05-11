#define INT_MIN -2147483648
#define INT_MAX 2147483647

/*@ assigns \nothing;
    ensures \result == \abs(x);
 */
unsigned abs(int x);

/*@ axiomatic Sum2 {
    logic integer sum2(integer x, integer y);
    logic integer sum2(integer x) = sum2(0, x);

    axiom init:
       \forall integer x, y; x > y && x >= 0 ==>
          sum2(x, y) == 0;
    axiom init_neg:
       \forall integer x, y; x < y && x < 0 ==>
          sum2(x, y) == 0;

    axiom step_dec:
       \forall integer x, y; y >= x >= 0 ==> sum2(x, y) == y * y + sum2(x, y - 1);

    axiom step_dec_neg:
       \forall integer x, y; y <= x < 0 ==> sum2(x, y) == y * y + sum2(x, y + 1);

    lemma positive:
       \forall integer x, y; sum2(x, y) >= 0;
    lemma monotonic:
       \forall integer x, y1, y2; y2 > y1 > x >= 0 ==> sum2(x, y2) >= sum2(x, y1);
    lemma negative_sum:
       \forall integer x, y; x >= 0 && y > 0 || x < 0 && y < 0 ==> sum2(x, y) == sum2(\abs(x), \abs(y));
    }
 */


/*@ requires sum2(x) <= INT_MAX;
    assigns \nothing;
    ensures \result >= 0;
    ensures \result == sum2(x - 1);
 */
int sum2(int x)
{
   int sum = x * x;
   x = abs(x);
   /*@ loop invariant 0 <= x;
       loop invariant sum == sum2(x, \at(x, Pre) - 1);
       loop invariant \forall integer i; x < i < \at(x, Pre) ==> i * i < INT_MAX;
       loop invariant sum < INT_MAX;
       loop assigns sum;
       loop variant x;
    */
   while (x--) {
      sum += x * x;
   }
   return sum;
}
