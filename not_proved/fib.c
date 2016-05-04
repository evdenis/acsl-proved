/*@ axiomatic Fib {
    logic integer fib(integer i);
    axiom nil:
       fib(0) == 0;
    axiom one:
       fib(1) == 1;
    axiom step_positive:
       \forall integer i; i >= 2 ==>
          fib(i) == fib(i - 1) + fib(i - 2);
    axiom step_negative:
       \forall integer i; i < 0 ==>
          fib(i) == fib(i + 2) - fib(i + 1);
    }
 */

/*
    assigns \nothing;
    ensures \result == fib(i);
 */
/*int fib(int i)
{
   int result = 0;

   while (i) {
      if (i) {
      } 
   }
}*/

#define INT_MAX 2147483647

/*@ requires fib(i) <= INT_MAX;
    decreases i for ;
    assigns \nothing;
    ensures \result == fib(i);
 */
int fib_rec(int i)
{
   if (i == 0 || i == 1) return i;
   if (i > 0) {
      return fib_rec(i - 1) + fib_rec(i - 2);
   } else {
      return fib_rec(i + 2) - fib_rec(i + 1);
   }
}

