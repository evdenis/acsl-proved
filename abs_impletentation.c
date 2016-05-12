#define INT_MIN -2147483648
#define INT_MAX 2147483647

/*@ assigns \nothing;
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
long abs(int a)
{
   long abs;

   abs = a;
   if (a < 0) {
      abs = -abs;
   }

   return abs;
}
