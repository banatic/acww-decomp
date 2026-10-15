/* func_0207e310 @ 0x0207e310, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_020996e0(int);
extern int func_0207e2ec(int, int, int);
extern int func_0207e2c8(int, int, int);
extern int func_0207e280(int, int, int);
extern int func_0207e238(int, int, int);
extern int func_0207e1f0(int, int, int);

int func_0207e310(int a, int b, int c)
{
    int result = 0;
    unsigned short *ptr = func_020996e0(a);
    int flag = 0;
    unsigned short val = *ptr;
    if (val >= 0x1431 && val <= 0x1470) {
        flag = 1;
    }
    if (flag != 0) {
        if (func_0207e2ec(a, b, c) != 0 || func_0207e2c8(a, b, c) != 0 || func_0207e280(a, b, c) != 0 ||
            func_0207e238(a, b, c) != 0 || func_0207e1f0(a, b, c) != 0) {
            result = 1;
        }
    }
    return result;
}
