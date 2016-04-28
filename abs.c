#define INT_MIN -2147483648
#define INT_MAX 2147483647

/*@ //requires INT_MIN < a <= INT_MAX;
    requires INT_MIN < a;
    assigns \nothing;
    ensures \result >= 0;
    behavior positive:
       assumes a > 0;
       ensures \result == a;
    behavior zero:
       assumes a == 0;
       ensures \result == 0;
       ensures \result == a;
    behavior negative:
       assumes a < 0;
       ensures \result == -a;
    complete behaviors;
    disjoint behaviors;
 */
int abs(int a)
{
   int abs;

   if (a < 0) {
      abs = -a;
   } else {
      abs = a;
   }

   return abs;
}
