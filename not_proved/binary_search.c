#ifdef OUT_OF_TASK
# define NULL ((void *)0)
#endif

/*@ requires \valid(a+(0..n-1));
    requires \forall integer i, j; 0 <= i < n && 0 <= j < n && i < j ==> a[i] <= a[j];
    assigns \nothing;
    behavior NOT_EXISTS:
       assumes !(\exists integer i; 0 <= i < n && a[i] == val) || n == 0;
       ensures \result == \null; 
    behavior EXISTS:
       assumes n > 0;
       assumes \exists integer i; 0 <= i < n && a[i] == val;
       ensures \exists integer i; 0 <= i < n && \result == (a + i);
       ensures (*\result) == val;
    complete behaviors;
    disjoint behaviors;
 */
int *bsearch(int a[], unsigned n, int val)
{
   unsigned left = 0;
   long right = n;

   /*@ loop invariant 0 <= left;
       loop invariant right <= n;
       //loop invariant left <= right; Найдите ошибку
       //loop invariant (\exists integer i; left <= i < right && a[i] == val) ==> a[left] <= val <= a[right];
       //loop invariant \forall integer i; 0 <= i < n && a[i] == val ==> a[left] <= val <= a[right] && left <= i <= right;
       //loop invariant \forall integer i; 0 <= i < n && a[i] == val ==> a[left] <= val <= a[right] && left <= i <= right;
       loop invariant \forall integer i; 0 <= i < n && a[i] == val ==> left <= i <= right;
       loop variant right - left;
    */
   while (left < right) {
      unsigned m = left + (right - left) / 2;

      if (a[m] < val) {
         left = m + 1;
      } else if (a[m] > val) {
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

   res = bsearch(a, ARRAY_SIZE(a), 0);
   printf("res: %d\n", *res);
   res = bsearch(b, ARRAY_SIZE(b), 1);
   printf("res: %d\n", *res);
   res = bsearch(c, ARRAY_SIZE(c), 10);
   printf("res: %p\n", res);
}
#endif

