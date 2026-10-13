/* func_0200545c @ 0x0200545c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_0200f290(int, int);
extern int func_020310c8(int);

int func_0200545c(int p0, int p1)
{
    int flag = data_020e54a8 ? 0 : 1;
    if (flag != 0) {
        goto ret1;
    }
    if (func_0200f290(p0, 3) != 0) {
        goto call2;
    }
ret1:
    return p1;
call2:
    return func_020310c8(0);
}
