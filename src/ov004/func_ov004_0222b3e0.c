/* func_ov004_0222b3e0 @ 0x0222b3e0, 0x6 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_0222b3e0(void *p, int a, int b)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
}
