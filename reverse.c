
/*@ requires size >= 0;
    requires \valid(a+(0..size-1));
    requires \valid(res+(0..size-1));
    assigns res[0..size-1];
    ensures \forall integer i; 0 <= i < size ==> res[i] == a[size - i - 1];
 */
void reverse(int a[], int res[], int size)
{
   int i;
   /*@ loop invariant -1 <= i < size; //Найдите ошибку
       loop invariant \forall integer j; i < j < size ==> res[j] == a[size - j - 1];
       loop assigns i, res[0..size-1];
       loop variant i;
    */
   for(i = size - 1; i >= 0; --i) {
      res[i] = a[size - i - 1];
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   int a[] = {1,2,3,4,5,6,7,8,9,10};
   int size = sizeof(a) / sizeof(a[0]);
   int b[size];
   for(int i = 0; i < size; ++i) {
      printf("%d ", a[i]);
   }
   printf("\n");
   reverse(a, b, size);
   for(int i = 0; i < size; ++i) {
      printf("%d ", b[i]);
   }
   printf("\n");
}
#endif
