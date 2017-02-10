/*@ requires 0 < n;
    assigns \nothing;
    ensures 0 <= \result < n;
*/
size_t random_number(size_t n);


/*@ requires \valid(a);
    requires \valid(b);
    requires a == b || a != b;
    assigns *a, *b;
    ensures *a == \old(*b);
    ensures *b == \old(*a);
*/
void swap(int *a, int *b);

/*@ axiomatic Count {
       logic integer Count{L}(int* a, integer m, integer n, int v) reads a[m..n-1];

       axiom CountSectionEmpty:
          \forall int *a, v, integer m, n;
              n <= m ==> Count(a, m, n, v) == 0;
       axiom CountSectionHit:
          \forall int *a, v, integer n, m;
              a[n] == v ==> Count(a, m, n + 1, v) == Count(a, m, n, v) + 1;
       axiom CountSectionMiss:
          \forall int *a, v, integer n, m;
              a[n] != v ==> Count(a, m, n + 1, v) == Count(a, m, n, v);
       axiom CountSectionRead{L1,L2}:
          \forall int *a, v, integer m, n;
              Unchanged{L1,L2}(a, m, n) ==> Count{L1}(a, m, n, v) == Count{L2}(a, m, n, v);
}
*/

/*@
  logic integer
    Count{L}(int* a, integer n, int v) = Count{L}(a, 0, n, v);

  lemma CountEmpty:
    \forall int *a, v, integer n;
      n <= 0  ==>  Count(a, n, v) == 0;

  lemma CountOneHit:
    \forall int *a, v, integer n;
      a[n] == v  ==>  Count(a, n + 1, v) == Count(a, n, v) + 1;

  lemma CountOneMiss:
    \forall int *a, v, integer n;
      a[n] != v  ==>  Count(a, n + 1, v) == Count(a, n, v);

  lemma CountRead{L1,L2}:
    \forall int *a, v, integer n;
      Unchanged{L1,L2}(a, n)  ==>  Count{L1}(a, n, v) == Count{L2}(a, n, v);
*/

/*@
   predicate Unchanged{K,L}(int* a, integer first, integer last) =
      \forall integer i; first <= i < last ==> \at(a[i],K) == \at(a[i],L);
   predicate Unchanged{K,L}(int* a, integer n) = Unchanged{K,L}(a, 0, n);
*/

/*@
   predicate MultisetUnchanged{L1,L2}(int* a, integer first, integer last) =
      \forall int v; Count{L1}(a, first, last, v) == Count{L2}(a, first, last, v);
   predicate MultisetUnchanged{L1,L2}(int* a, integer n) =
      MultisetUnchanged{L1,L2}(a, 0, n);
*/


/*@
  lemma
    UnchangedImpliesMultisetUnchanged{L1,L2}:
      \forall int *a, integer k, n;
        Unchanged{L1,L2}(a, k, n) ==>
        MultisetUnchanged{L1,L2}(a, k, n);

  lemma
    MultisetUnchangedUnion{L1,L2}:
      \forall int *a, integer k, n;
        0 <= k <= n                        ==>
        MultisetUnchanged{L1,L2}(a, 0, k)  ==>
        MultisetUnchanged{L1,L2}(a, k, n)  ==>
        MultisetUnchanged{L1,L2}(a, 0, n); 

  lemma
    MultisetUnchangedTransitive{L1,L2,L3}:
      \forall int *a, integer n;
        MultisetUnchanged{L1,L2}(a, n)  ==>
        MultisetUnchanged{L2,L3}(a, n)  ==>
        MultisetUnchanged{L1,L3}(a, n);
*/

/*@ requires \valid(a + (0..n-1));
    assigns a[0..n-1];
    ensures MultisetUnchanged{Here,Old}(a,n);
*/
void random_shuffle(int* a, size_t n)
{
   if (n > 0) {
      /*@ loop invariant bounds: 1 <= i <= n;
          loop invariant reorder: MultisetUnchanged{Here,Pre}(a,0,i);
          loop invariant unchanged: Unchanged{Here,Pre}(a,i,n);
          loop assigns i, a[0..n-1];
          loop variant n - i;
       */
      for (size_t i = 1; i < n; ++i) {
         const size_t j = random_number(i) + 1;
         //@ ghost Before:
         swap(&a[j], &a[i]);
         //@ assert reorder: MultisetUnchanged{Here,Before}(a, 0, j);
         //@ assert reorder: MultisetUnchanged{Here,Before}(a, j+1, i);
      }
   }
}

