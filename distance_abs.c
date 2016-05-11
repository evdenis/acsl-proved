#define INT_MIN -2147483648
#define INT_MAX 2147483647


/*@ requires \true;
    //requires a > INT_MIN; // Найдите ошибку в спецификации. Ответ.
    //requires b > INT_MIN; // Найдите ошибку в спецификации. Ответ.
    assigns \nothing;
    ensures \result == \abs(\abs(a) - \abs(b));
 */
unsigned distance_abs(int a, int b)
{
   unsigned ua = a < 0 ? -a : a;
   unsigned ub = b < 0 ? -b : b;
   //unsigned ua = a < 0 ? ((unsigned)-((long)a)) : a; // Найдите ошибку в реализации. Ответ.
   //unsigned ub = b < 0 ? ((unsigned)-((long)b)) : b; // Найдите ошибку в реализации. Ответ.

   return ua > ub ? ua - ub : ub - ua;
}
