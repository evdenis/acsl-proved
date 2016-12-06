
/*@ //requires \nothing;
    requires \true;
    assigns \nothing;
    ensures \result == \max(a, b) - \min(a, b);
 */
unsigned distance(unsigned a, unsigned b)
{
   return (a > b) ? (a - b) : (b - a);
}

#ifdef OUT_OF_TASK
#include <stdio.h>
int main(void)
{
   printf("res: %d\n", distance(100, 80));
   return 0;
}
#endif
