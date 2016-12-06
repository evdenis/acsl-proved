#define SPEC_INT_MAX 32767

/*@ requires size >= 0;
    requires \valid(p+(0..size-1));
    requires val + 2 < SPEC_INT_MAX;
    assigns p[0..size-1];
    ensures \forall integer j; 0 <= j < size && j % 3 != 0 ==> p[j] == val + j % 3;
    ensures \forall integer j; 0 <= j < size && j % 3 == 0 ==> p[j] == \old(p[j]);
 */
void set_skip_third(int *p, int size, int val)
{
   int i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i && j % 3 != 0 ==> p[j] == val + j % 3;
       loop invariant \forall integer j; 0 <= j < i && j % 3 == 0 ==> p[j] == \at(p[\at(j,Here)], Pre);
       loop assigns i, p[0..i-1];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      if (i % 3 != 0) {
         p[i] = val + i % 3;
      }
   }
}

#ifdef OUT_OF_TASK
#include <stdio.h>

void print_int_array(int a[], int size)
{
   for(int i = 0; i < size - 1; ++i) {
      printf("%d, ", a[i]);
   }
   printf("%d", a[size - 1]);
}

int main(void)
{
   int a[] = {1,2,3,4,5,6,7,8,9,10};
   int size = sizeof(a) / sizeof(a[0]);
   
   printf("orig: ");
   print_int_array(a, size);
   printf("\n");
   
   set_skip_third(a, size, 5);
   
   printf("res: ");
   print_int_array(a, size);
   printf("\n");
   
   return 0;
}
#endif
