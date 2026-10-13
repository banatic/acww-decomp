/* func_02073878 @ 0x02073878, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02073878(char *p, int val)
{
    char *q = p;
    q += 0xC4;
    *(int *) q = val;
    p += 0xCC;
    *(int *) p = val;
}
