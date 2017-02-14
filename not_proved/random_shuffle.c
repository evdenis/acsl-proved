/*@ requires 0 < n;
    assigns \nothing;
    ensures 0 <= \result < n;
*/
size_t random_number(size_t n);

/*@ predicate Swap{L1,L2}(int *a, integer i, integer j) =
       \at(a[i],L1) == \at(a[j],L2) &&
       \at(a[j],L1) == \at(a[i],L2) &&
       \forall integer k; k != i && k != j
          ==> \at(a[k],L1) == \at(a[k],L2);
 */

/*@ requires \valid(t+i);
    requires \valid(t+j);
    assigns t[i],t[j];
    ensures Swap{Old,Here}(t,i,j);
 */
void swap(int t[], int i, int j)
{
   int tmp = t[i];
   t[i] = t[j];
   t[j] = tmp;
}

/*@
   predicate Unchanged{K,L}(int* a, integer first, integer last) =
      \forall integer i; first <= i < last ==> \at(a[i],K) == \at(a[i],L);
   predicate Unchanged{K,L}(int* a, integer n) = Unchanged{K,L}(a, 0, n);
*/

/*@ inductive Permut{L1,L2}(int *a, integer l, integer h) {
    case Permut_refl{L}:
      \forall int *a, integer l, h; Permut{L,L}(a, l, h);
    case Permut_sym{L1,L2}:
      \forall int *a, integer l, h;
        Permut{L1,L2}(a, l, h) ==> Permut{L2,L1}(a, l, h);
    case Permut_trans{L1,L2,L3}:
      \forall int *a, integer l, h;
        Permut{L1,L2}(a, l, h) && Permut{L2,L3}(a, l, h) ==>
          Permut{L1,L3}(a, l, h);
    case Permut_swap{L1,L2}:
      \forall int *a, integer l, h, i, j;
         l <= i <= h && l <= j <= h && Swap{L1,L2}(a, i, j) ==>
       Permut{L1,L2}(a, l, h);
   }
 */

/*@ requires \valid(a + (0..n-1));
    assigns a[0..n-1];
    ensures Permut{Pre,Here}(a, 0, n-1);
*/
void random_shuffle(int* a, size_t n)
{
   if (n > 0) {
      /*@ loop invariant bounds: 1 <= i <= n;
          loop invariant reorder: Permut{Here,Pre}(a,0,n-1);
          loop invariant unchanged: Unchanged{Here,Pre}(a,i,n);
          loop assigns i, a[0..n-1];
          loop variant n - i;
       */
      for (size_t i = 1; i < n; ++i) {
         const size_t j = random_number(i) + (size_t) 1;
         //@ ghost Before:
         swap(a, j, i);
         //@ assert reorder: Permut{Here,Before}(a, 0, j);
         //@ assert reorder: Permut{Here,Before}(a, j+1, i);
         //@ assert reorder: Permut{Here,Before}(a, 0, n-1);
      }
   }
}

