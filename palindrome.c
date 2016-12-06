/*@ requires \valid(a+(0..size-1));
    assigns \nothing;
    ensures \result == 0 || \result == 1;
    behavior nil:
       assumes size == 0;
       ensures \result == 1;
    behavior palindrome:
       assumes size > 0;
       assumes \forall integer i; 0 <= i < size ==> a[i] == a[size - i - 1];
       ensures \result == 1;
    behavior non_palindrome:
       assumes size > 0;
       assumes \exists integer i; 0 <= i < size && a[i] != a[size - i - 1];
       ensures \result == 0;
    complete behaviors;
    disjoint behaviors;
 */
int palindrome(int a[], unsigned size)
{
   int res = 1;
   unsigned i;

   /*@ loop invariant 0 <= i <= size / 2;
       loop invariant (\forall integer j; 0 <= j < i ==> a[j] == a[size - j - 1]) <==> (res == 1);
       //loop invariant (a[i] != a[size - i - 1]) <==> (res == 0);
       loop invariant res == 0 || res == 1;
       loop assigns res;
       loop variant size - i;
    */
   for(i = 0; i < size / 2; ++i) {
      if (a[i] != a[size - i - 1]) {
         res = 0;
         break;
      }
   }
   return res;
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   int a[] = {1,2,3,4,5,6,7,8,9,10};
   int b[] = {1,2,3,4,5,5,4,3,2,1};
   int size = sizeof(a) / sizeof(a[0]);
   
   printf("res: %d\n", palindrome(a, size));
   printf("res: %d\n", palindrome(b, size));
   
   return 0;
}
#endif
