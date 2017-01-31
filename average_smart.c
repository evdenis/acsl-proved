
/*@ assigns \nothing;
    ensures \result == (a + b) / 2;
 */
unsigned average_smart(unsigned a, unsigned b)
{
   //@ assert a >> 1U == a / 2;
   //@ assert b >> 1U == b / 2;
   //@ ghost unsigned a1 = a % 2;
   //@ ghost unsigned b1 = b % 2;
   //@ assert (a & 1U) == a1;
   //@ assert (b & 1U) == b1;
   //@ assert (a & b & 1U) == ((a + b) / 2) - ((a / 2) + (b / 2));
   return (a >> 1) + (b >> 1) + (a & b & 1U);
}

#ifdef OUT_OF_TASK
#include <limits.h>
#include <stdio.h>

int main(void)
{
   printf("res: %d\n", average_smart(3,30));
   printf("res: %d\n", average_smart(5,20));
   printf("res: %d\n", average_smart(7,10));
   printf("res: %d\n", average_smart(2,15));
   return 0;
}
#endif
