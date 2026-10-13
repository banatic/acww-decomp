/* func_02030890 @ 0x02030890, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020308a4(int, int);

void func_02030890(int *param)
{
    int a;
    int b;
    int *ptr;

    ptr = param;
    a = *ptr >> 13;
    b = *(ptr + 2) >> 13;
    func_020308a4(a, b);
}
