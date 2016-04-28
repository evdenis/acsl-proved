
/*@ assigns \nothing;
    ensures \result == 0 || \result == 1 || \result == -1;
    behavior positive:
       assumes x > 0;
       ensures \result == 1;
    behavior zero:
       assumes x == 0;
       ensures \result == 0;
    behavior negative:
       assumes x < 0;
       ensures \result == -1;
    complete behaviors;
    disjoint behaviors;
 */
int sign(int x)
{
   return (x > 0) - (x < 0);
}

/*@ assigns \nothing;
    ensures \result == 0 || \result == 1 || \result == -1;
    behavior positive:
       assumes x > 0;
       ensures \result == 1;
    behavior zero:
       assumes x == 0;
       ensures \result == 0;
    behavior negative:
       assumes x < 0;
       ensures \result == -1;
    complete behaviors;
    disjoint behaviors;
 */
/*int sign2(int x)
{
    // assumes 32-bit int and 2s complement signed shifts work (implementation defined by C spec)
    return (x>>31) | ((unsigned)-x >> 31);
}*/
