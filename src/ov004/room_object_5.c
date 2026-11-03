/* room_object_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220ce50 @ 0x0220ce50, 0xc bytes, Thumb
 * func_ov004_0220ce44 @ 0x0220ce44, 0xc bytes, Thumb
 * func_ov004_0220ce2c @ 0x0220ce2c, 0x18 bytes, Thumb
 * func_ov004_0220ce20 @ 0x0220ce20, 0xc bytes, Thumb
 */

extern int func_ov004_0220ccf8(int, int);
extern int func_ov004_0220cdd8(int a, int b);

void func_ov004_0220ce50(int a)
{
    func_ov004_0220ccf8(a, 6);
}

int func_ov004_0220ce44(int a)
{
    return func_ov004_0220cdd8(a, 1);
}

int func_ov004_0220ce2c(int arg0)
{
    if (func_ov004_0220ce44(arg0) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov004_0220ce20(int a)
{
    return func_ov004_0220cdd8(a, 1);
}
