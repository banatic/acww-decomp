/* func_02030890 @ 0x02030890, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020308a4(int, int);

int func_02030890(int *param)
{
    int a;
    int b;
    int *ptr;

    ptr = param;
    a = *ptr >> 13;
    b = *(ptr + 2) >> 13;
    return func_020308a4(a, b);
}
