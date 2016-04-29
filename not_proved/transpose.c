
/*@ requires \valid(dest);
    requires \valid(src);
    assigns dest;
 */
void transpose(int *dest, int *src, int src_h, int src_w)
{
	int i, j;
	int (*d)[src_h] = dest, (*s)[src_w] = src;

   /*@ loop invariant 0 <= i <= src_h;
       loop variant src_h - i;
    */
	for (i = 0; i < src_h; i++)
      /*@ loop invariant 0 <= j <= src_w;
          loop vartiant src_w - j;
       */
		for (j = 0; j < src_w; j++)
			d[j][i] = s[i][j];
}

#ifdef OUT_OF_TASK 
#include <stdio.h>
int main()
{
	int i, j;
	int a[3][5] = {{ 0, 1, 2, 3, 4 },
			  { 5, 6, 7, 8, 9 },
			  { 1, 0, 0, 0, 42}};
	int b[5][3];
	transpose(b, a, 3, 5);
 
	for (i = 0; i < 5; i++)
		for (j = 0; j < 3; j++)
			printf("%d%c", b[i][j], j == 2 ? '\n' : ' ');
	return 0;
}
#endif
