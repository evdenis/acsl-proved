#define INT_MIN -2147483648
#define INT_MAX 2147483647


/*@ requires size >= 0;
    requires \valid(result+(0..size-1));
    requires \valid(a+(0..size-1));
    requires \valid(b+(0..size-1));
    requires \forall integer i; 0 <= i < size ==> INT_MIN <= a[i] + b[i] <= INT_MAX;
    assigns result[0..size-1];
    ensures \forall integer i; 0 <= i < size ==> result[i] == a[i] + b[i];
 */
void arrays_sum(int result[], int a[], int b[], int size)
{
   int i;
   /*@ loop invariant 0 <= i <= size;
       loop invariant \forall integer j; 0 <= j < i ==> result[j] == a[j] + b[j];
       loop variant size - i;
    */
   for(i = 0; i < size; ++i) {
      result[i] = a[i] + b[i];
   }
}
