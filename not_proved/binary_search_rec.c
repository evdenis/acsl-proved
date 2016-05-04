
/*@ requires \valid(a+(left..right-1));
    requires \forall integer i, j; left <= i < right && left <= j < right && i < j ==> a[i] <= a[j];
    assigns \nothing;
    behavior NOT_EXISTS:
       assumes ! \exists integer i; left <= i < right && a[i] == val;
       ensures \result == \null; 
    behavior EXISTS:
       assumes \exists integer i; left <= i < right && a[i] == val;
       ensures \exists integer i; left <= i < right && \result == a + i;
       ensures *\result == val;
    complete behaviors;
    disjoint behaviors;
 */
int *bsearch_rec(int a[], unsigned left, unsigned right, int val)
{
   unsigned m = left + (right - left) / 2;

   if (left > right) {
      return NULL;
   }

   if (a[m] < val) {
      left = m + 1;
   } else if (a[m] > val) {
      right = m - 1;
   } else {
      return &a[m];
   }

   return bsearch_rec(a, left, right, val);
}

/*@ requires \valid(a+(0..n-1));
    requires \forall integer i, j; 0 <= i < n && 0 <= j < n && i < j ==> a[i] <= a[j];
    assigns \nothing;
    behavior NOT_EXISTS:
       assumes ! \exists integer i; 0 <= i < n && a[i] == val;
       ensures \result == \null; 
    behavior EXISTS:
       assumes \exists integer i; 0 <= i < n && a[i] == val;
       ensures \exists integer i; 0 <= i < n && \result == a + i;
       ensures *\result == val;
    complete behaviors;
    disjoint behaviors;
 */
int *bsearch(int a[], unsigned n, int val)
{
   return bsearch_rec(a, 0, n, val);
}
