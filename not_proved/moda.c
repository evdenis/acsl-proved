/*@ axiomatic Count {
    logic integer count{L}(int *a, integer i, integer size, int val);
    axiom zero:
       \forall int *a, val, integer size;
          (size <= 0) ==> count(a, 0, 0, val) == 0;
    axiom step{L}:
       \forall int *a, val, integer size;
          (a[size] == val ==> count(a, size, val) == 1 + count(a, size-1, val)) &&
          (a[size] != val ==> count(a, size, val) == count(a, size-1, val));
    lemma increasing:
       \forall int *a, val, integer size;
          count(a, size, val) >= count(a, size - 1, val);
    lemma positive:
       \forall int *a, val, integer size;
          count(a, size, val) >= 0;
    }
 */

/*@ requires \valid(a+(0..size-1));
    assigns \nothing;
    behavior zero:
       assumes size == 0;
       ensures \result == -1;
    behavior positive:
       assumes size > 0;
       ensures \exists integer i; 0 <= i < size && a[i] == \result;
       ensures \forall integer i; 0 <= i < size ==> count(a, size, \result) >= count(a, size, a[i]);
    complete behaviors;
    disjoint behaviors;
 */
int moda(int a[], unsigned size)
{
   unsigned max_times = 0;
   unsigned element = 0;
   unsigned i;

   if (size == 0) {
      return -1;
   }

   /*@ loop invariant 0 <= i <= size;
       loop invariant 0 <= max_times <= size;
       loop invariant 0 <= element <= i;
       loop invariant 0 <= element < size;
       loop invariant \forall integer j; 0 <= j < i ==> count(a, size, a[element]) >= count(a, size, a[j]);
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      unsigned times = 0;
      unsigned j;

      /*@ loop invariant i <= j <= size;
          loop invariant 0 <= times <= j;
          loop invariant \forall integer k; i <= k < j ==> count(a, j, a[i]) == times;
          loop variant size - j;
       */
      for(j = i; j < size; ++j) {
         if (a[j] == a[i]) {
            ++times;
         }
      }
      if (times > max_times) {
         max_times = times;
         element = i;
      }
   }

   // assert \exists integer i; 0 <= i < size && a[i] == a[element];

   return a[element];
}
