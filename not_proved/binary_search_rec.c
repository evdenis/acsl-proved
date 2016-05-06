#ifdef OUT_OF_TASK
# define NULL ((void*)0)
#endif

/*@ requires \valid(a+(left..right-1));
    requires \forall integer i, j; left <= i < j < right ==> a[i] <= a[j];
    decreases right - left;
    assigns \nothing;
    behavior NOT_EXISTS:
       assumes \forall integer i; left <= i < right ==> a[i] != key;
       ensures \result == \null; 
    behavior EXISTS:
       assumes \exists integer i; left <= i < right && a[i] == key;
       ensures \exists integer i; left <= i < right && \result == (a + i);
       ensures (*\result) == key;
    complete behaviors;
    disjoint behaviors;
 */
int *bsearch_rec(int a[], unsigned left, unsigned right, int key)
{
   unsigned m = left + (right - left) / 2;

   if (left > right) {
      return NULL;
   }

   if (a[m] < key) {
      left = m + 1;
   } else if (a[m] > key) {
      right = m - 1;
   } else {
      return &a[m];
   }

   return bsearch_rec(a, left, right, key);
}

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
int *bsearch(int a[], unsigned n, int key)
{
   return bsearch_rec(a, 0, n, key);
}
