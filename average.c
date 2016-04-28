/*@ assigns \nothing;
    ensures \result == (a+b)/2;
*/
int average(int a, int b)
{
   int average = 0;

	int greater;
	int smaller;
	if (a > b) {
	   greater = a;
	   smaller = b;
	} else {
	   greater = b;
	   smaller = a;
	}
	if (a >= 0 && b >= 0) {
	   average = smaller + (greater - smaller) / 2;
	} else if (a < 0 && b < 0) {
	   average = greater + (smaller - greater) / 2;
	} else if (a >= 0 && b <= 0 || a <= 0 && b >= 0) {
	   average = (a + b) / 2;
	}

   return average;
}
