#ifdef OUT_OF_TASK
# define NULL ((void *)0)
#endif

/*@ requires \valid(a+(0..n-1));
    requires \forall integer i, j; 0 <= i < j < n ==> a[i] <= a[j];
    assigns \nothing;
    behavior NOT_EXISTS:
       assumes \forall integer i; 0 <= i < n ==> a[i] != key;
       ensures \result == \null; 
    behavior EXISTS:
       assumes \exists integer i; 0 <= i < n && a[i] == key;
       ensures \exists integer i; 0 <= i < n && \result == (a + i);
       ensures (*\result) == key;
    complete behaviors;
    disjoint behaviors;
 */
int *spec_bsearch(int a[], unsigned n, int key)
{
   unsigned left = 0;
   long right = ((long)n) - 1;

   /*@ loop invariant 0 <= left;
       loop invariant right < n;
       //loop invariant left <= right; //Найдите ошибку
       loop invariant \forall integer i; 0 <= i < n && a[i] == key ==> left <= i <= right;
       loop invariant \forall integer i; 0 <= i < n && a[i] == key ==> a[left] <= key <= a[right];
       loop variant right - left;
    */
   while (left <= right) {
      unsigned m = left + (right - left) / 2;

      if (a[m] < key) {
         left = m + 1;
      } else if (a[m] > key) {
         right = ((long)m) - 1;
      } else {
         return &a[m];
      }
   }
   return NULL;
}


#ifdef OUT_OF_TASK
#include <stdio.h>
#define ARRAY_SIZE(array) (sizeof(array)/sizeof((array)[0]))
int main(void)
{
   int a[] = {0};
   int b[] = {0,1};
   int c[] = {0,1,2,3,4,5};
   int *res;

   res = spec_bsearch(a, ARRAY_SIZE(a), 0);
   printf("res: %d\n", *res);
   res = spec_bsearch(b, ARRAY_SIZE(b), 1);
   printf("res: %d\n", *res);
   res = spec_bsearch(c, ARRAY_SIZE(c), 10);
   printf("res: %p\n", res);
}
#endif

