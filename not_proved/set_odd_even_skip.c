
/*@ requires \valid(a+(0..n-1));
    assigns a[0..n-1];
    ensures \forall integer i; 0 <= i < n && (i % 2 == 0) && (i % 3 != 0) ==> a[i] == 1;
    ensures \forall integer i; 0 <= i < n && (i % 2 == 1) && (i % 3 != 0) ==> a[i] == 0;
    ensures \forall integer i; 0 <= i < n && (i % 3 == 0) ==> a[i] == \old(a[i]);
 */
void set_odd_even_skip(int a[], unsigned n)
{
   unsigned i;
   /*@ loop invariant 0 <= i <= n;
       loop invariant \forall integer j; 0 <= j < i && j % 3 == 0 ==> a[j] == \at(a[\at(j,Here)], Pre);
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 0 && j % 3 != 0 ==> a[j] == 1;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 1 && j % 3 != 0 ==> a[j] == 0;
       loop assigns a[0..n-1];
       loop variant n - i;
    */
   for(i = 0; i < n; ++i) {
      if (i % 3 == 0) {
         continue;
      } else if (i % 2 == 0) {
         a[i] = 1;
      } else {
         a[i] = 0;
      }
   }
}

