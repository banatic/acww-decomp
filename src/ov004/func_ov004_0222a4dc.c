/* func_ov004_0222a4dc @ 0x0222a4dc, 0x8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_0222a4dc(char *p, int a, int b, int c)
{
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(short *) (p + 8) = (short) c;
}
