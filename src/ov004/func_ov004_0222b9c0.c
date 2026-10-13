/* func_ov004_0222b9c0 @ 0x0222b9c0, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_0222b9c0(void *p, int a, int b, short c, unsigned char d)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
    *(short *) ((char *) p + 8) = c;
    *((unsigned char *) p + 0xa) = d;
}
