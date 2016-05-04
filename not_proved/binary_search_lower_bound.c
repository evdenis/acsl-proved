#ifdef OUT_OF_TASK
# define NULL ((void *)0)
#endif

int *bsearch_lower_bound(int a[], unsigned n, int key)
{
   unsigned left = 0;
   long right = n - 1;

   while (left <= right) {
      unsigned m = left + (right - left) / 2;
      int val = a[m];

      if (val < key) {
         left = m + 1;
      } else {
      }
   }

   return NULL;
}
