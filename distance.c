#include <stdio.h>

/*@ //requires \nothing;
    requires \true;
    assigns \nothing;
    ensures \result == \max(a, b) - \min(a, b);
 */
unsigned distance(unsigned a, unsigned b)
{
   unsigned res;
   a > b && (res = a - b) || (res = b - a);
   return res;
}

int main(void)
{
   printf("%d\n", distance(100, 80));
   return 0;
}