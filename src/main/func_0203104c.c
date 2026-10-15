/* func_0203104c @ 0x0203104c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02031060(int, int);

int func_0203104c(int *arg0)
{
    int r0;
    int r1;
    int *ptr;

    ptr = arg0;
    r0 = *ptr >> 13;
    r1 = *(ptr + 2) >> 13;
    return func_02031060(r0, r1);
}
