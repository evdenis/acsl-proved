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
int *bsearch_lower_bound(int a[], unsigned n, int key)
{
   unsigned left = 0;
   long right = ((long)n) - 1;

   /*@ loop invariant 0 <= left;
       loop invariant right < n;
       loop invariant \forall integer i; 0 <= i < n && a[i] == key ==> left <= i;
       loop invariant \forall integer i; 0 <= i < n && a[i] == key ==> a[left] <= key;
       loop variant right - left;
    */
   while (left <= right) {
      unsigned m = left + (right - left) / 2;
      int val = a[m];

      if (val < key) {
         left = m + 1;
      } else {
         right = m;
      }
   }

   if (left > right) {
      return NULL;
   } else {
      return &a[left];
   }
}
