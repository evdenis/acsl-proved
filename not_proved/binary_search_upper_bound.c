#ifdef OUT_OF_TASK
# define NULL ((void *)0)
#endif

/*@ requires \valid(a+(0..n-1));
    requires \forall integer i, j; 0 <= i <= j < n ==> a[i] <= a[j];
    assigns \nothing;
    behavior OK:
       assumes \exists integer i; 0 <= i < n && a[i] == key;
       ensures \exists integer i; 0 <= i < n && \result == (a + i);
       ensures *\result == key;
       ensures ! \exists integer i; 0 <= i < n && a[i] == key && (a + i) < \result;
       ensures \forall integer i; 0 <= i < (\result - a) && a[i] < *\result;
       ensures \result != a ==> *(\result - 1) < *\result;
    behavior FAIL:
       assumes ! \exists integer i; 0 <= i < n && a[i] == key;
       ensures \result == \null;
    disjoint behaviors;
    complete behaviors;
 */
int *bsearch_upper_bound(int a[], unsigned n, int key)
{
   unsigned left = 0;
   long right = n - 1;

   while (left <= right) {
      unsigned m = left + (right - left) / 2;
      int val = a[m];

      if (key < val) {
         right = middle;
      } else {
         left = m + 1;
      }
   }

   if (left > right) {
      return NULL;
   } else {
      return &a[right];
   }
}
