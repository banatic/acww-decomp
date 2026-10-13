/* func_0204d4bc @ 0x0204d4bc, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;
extern int func_0204d888(int, int);
extern int func_0204d7a8(int, int, int, int);
extern void func_0204d530(int, int, int);

int func_0204d4bc(int a, int b, int c, int d)
{
    int mode = 4;
    int mi = b & 0xfff;
    int result = 0;
    unsigned char g = data_020e54a8;
    int flag1 = (g == 0) ? 1 : result;
    if (flag1 != 0) {
        mode = 0;
    } else {
        int flag2 = (g == 1) ? 1 : 0;
        if (flag2 != 0) {
            mode = 1;
        }
    }

    if (mode != 4) {
        if (func_0204d888(mode, mi) == 1) {
            result = func_0204d7a8(mode, mi, d, 4);
            func_0204d530(a, result, c);
        }
    }
    return result;
}
