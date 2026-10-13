/* func_ov004_0220da54 @ 0x0220da54, 0x1a bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

void func_ov004_0220da54(int *o)
{
    unsigned i;
    int *p;
    o[10] = 0;
    i = 0;
    do {
        o[i] = 0;
        p = o + i;
        p[2] = 0;
        p[6] = 0;
        p[8] = 0;
        i++;
    } while (i < 2);
}
