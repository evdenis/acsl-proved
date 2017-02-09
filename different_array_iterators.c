
/*@ requires size >= 2;
    requires \valid(a + (0..size-1));
    requires \valid(max);
    requires \valid(min);
    requires max != min;
    assigns *max, *min;
    ensures 0 <= *max < size;
    ensures 0 <= *min < size;
    behavior max:
       ensures \forall integer i; (0 <= i < size) && (i % 2 == 0) ==> a[i] <= a[*max];
    behavior min:
       ensures \forall integer i; (0 <= i < size) && (i % 2 == 1) ==> a[*min] <= a[i];
*/
void max_min_in_array(int *a, int size, int *max, int *min)
{
   int mx = 0;
   int mn = 1;

   /*@ loop invariant 2 <= i <= size;
       loop invariant 0 <= mx < size;
       loop invariant 1 <= mn < size;
       for max: loop invariant \forall integer j; (0 <= j < i) && (j % 2 == 0) ==> a[j] <= a[mx];
       for min: loop invariant \forall integer j; (0 <= j < i) && (j % 2 == 1) ==> a[mn] <= a[j];
       loop variant size - i;
    */
   for(int i = 2; i < size; ++i) {
      if (i % 2) {
         if (a[mn] > a[i]) mn = i;
      } else {
         if (a[mx] < a[i]) mx = i;
      }
   }

   *max = mx;
   *min = mn;
}

/*@ requires size > 0;
    requires \valid(a + (0..size - 1));
    ensures 0 <= \result < size;
    ensures \forall integer i; 0 <= i < size ==> a[i] <= a[\result];
 */
int max_in_array(int *a, int size)
{
   int j = 0;
   int max = a[0];

   /*@ loop invariant 1 <= i <= size;
       loop invariant 0 <= j < i;
       loop invariant max == a[j];
       loop invariant \forall integer k; 0 <= k < i ==> a[k] <= max;
       loop variant size - i;
    */
   for(int i = 1; i < size; ++i) {
      if (max < a[i]) {
         j = i;
         max = a[i];
      }
   }

   return j;
}

#define INT_MAX 2147483647

/* lemma odd_even:
       \forall integer i; (i >= 0) ==> (i % 2 == 0) || (i % 2 == 1);
    lemma odd_next:
       \forall integer i; (i >= 0) && (i % 2 == 0) ==> ((i + 1) % 2) == 1;
    lemma even_next:
       \forall integer i; (i >= 0) && (i % 2 == 1) ==> ((i + 1) % 2) == 0;
 */

/*@ requires size > 0;
    requires size <= INT_MAX - 1;
    requires \valid(a + (0..size - 1));
    ensures 0 <= \result < size;
    ensures \result % 2 == 0;
    ensures \forall integer i; (0 <= i < size) && (i % 2 == 0) ==> a[i] <= a[\result];
 */
int max_in_array_even(int *a, int size)
{
   int j = 0;
   int max = a[0];

   /*@ loop invariant 2 <= i <= size + 1;
       loop invariant 0 <= j < i;
       loop invariant i % 2 == 0 && j % 2 == 0;
       loop invariant max == a[j];
       loop invariant \forall integer k; (0 <= k < i) && (k % 2 == 0) ==> a[k] <= max;
       loop variant size - i;
    */
   for(int i = 2; i < size; i += 2) {
      if (max < a[i]) {
         j = i;
         max = a[i];
      }
   }

   return j;
}
