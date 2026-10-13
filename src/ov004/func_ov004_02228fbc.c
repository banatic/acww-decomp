/* func_ov004_02228fbc @ 0x02228fbc, 0x8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_02228fbc(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}
