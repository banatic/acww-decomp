/* func_ov004_0223c5a4 @ 0x0223c5a4, 0x14 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223c5b8(int, int);

void func_ov004_0223c5a4(int *param)
{
    int a;
    int b;
    int *ptr;

    ptr = param;
    a = *ptr >> 13;
    b = *(ptr + 2) >> 13;
    func_ov004_0223c5b8(a, b);
}
