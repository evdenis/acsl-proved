/*@ requires n > 0;
    requires \valid(p + (0..n-1));
    assigns \nothing;
    ensures 0 <= \result < n;
    ensures \forall int i; 0 <= i < n ==> p[\result] >= p[i];
*/
int max_in_array(int *p, int n)
{
	int max_idx = 0;
   int max = p[max_idx];

   /*@ loop invariant 0 <= i <= n;
       loop invariant 0 <= max_idx < n;
       loop invariant 0 <= max_idx <= i;
       loop invariant max == p[max_idx];
       loop invariant \forall int j; 0 <= j < i ==> p[max_idx] >= p[j];
       loop invariant \forall int j; 0 <= j < i ==> max >= p[j];
       loop variant n - i;
	*/
	for (int i = 0; i < n; i++) {
		if (max < p[i]) {
			max_idx = i;
         max = p[i];
      }
	}

	return max_idx;
}

#ifdef OUT_OF_TASK

#include <stdio.h> 

int main(int argc, char **argv)
{
   int max[] = {1, 2, 3, 4, 5, -1, -10, 6, 32, 101};
   int res = max_in_array(max, sizeof(max)/sizeof(int));
   printf("max: %d\n", max[res]);
   return 0;
}

#endif
