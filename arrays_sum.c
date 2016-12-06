#define SPEC_INT_MIN -2147483648
#define SPEC_INT_MAX 2147483647


/*@ requires size >= 0;
    requires \valid(result+(0..size-1));
    requires \valid(a+(0..size-1));
    requires \valid(b+(0..size-1));
    requires \forall integer i; 0 <= i < size ==> SPEC_INT_MIN <= a[i] + b[i] <= SPEC_INT_MAX;
    assigns result[0..size-1];
    ensures \forall integer i; 0 <= i < size ==> result[i] == a[i] + b[i];
 */
void arrays_sum(int result[], int a[], int b[], int size)
{
   int i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i ==> result[j] == a[j] + b[j];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      result[i] = a[i] + b[i];
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>

int main(void)
{
   int a[] = {1,2,3,4,5,6,7,8,9,10};
   int b[] = {-1,2,-3,4,-5,6,-7,8,-9,10};
   int size = sizeof(a) / sizeof(a[0]);
   int result[size];
   
   arrays_sum(result, a, b, size);
   printf("res: ");
   for(int i = 0; i < size - 1; ++i)
      printf("%d, ", result[i]);
   printf("%d", result[size - 1]);
   printf("\n");
   
   return 0;
}
#endif
