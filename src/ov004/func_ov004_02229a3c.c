/* func_ov004_02229a3c @ 0x02229a3c, 0x6 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_02229a3c(void *p, int a, int b)
{
    *(int *) p = a;
    *(int *) ((char *) p + 4) = b;
}
