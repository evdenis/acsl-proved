/*@ requires size >= 0;
    requires \valid(p+(0..size-1));
    assigns p[0..size-1];
    ensures \forall integer j; 0 <= j < size && j % 2 != 0 ==> p[j] == val;
    ensures \forall integer j; 0 <= j < size && j % 2 == 0 ==> p[j] == \old(p[j]);
 */
void set_odd(int *p, int size, int val)
{
   int i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i && j % 2 != 0 ==> p[j] == val;
       loop invariant \forall integer j; 0 <= j < i && j % 2 == 0 ==>
          p[j] == \at(p[\at(j,Here)], Pre);
       loop assigns i, p[0..i-1];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      if (i % 2 != 0) {
         p[i] = val;
      }
   }
}
