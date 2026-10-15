/* func_020177e0 @ 0x020177e0, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bd4(void);
extern int func_02057d0c(int, int);
extern void func_02016764(int, int, int, unsigned short, int, int, int, int);
extern int func_0200442c(int, int, int, int);
extern int func_020164a0(int, int);
extern void func_02054768(int, int, int);
extern void func_02019af0(int, int);
extern unsigned short data_020c80f8;

int func_020177e0(int a, int b)
{
    if (func_02057bd4() && func_02057d0c(5, b)) {
        func_02016764(b + 0x334, b, 0x27, data_020c80f8, 1, 0x1000, 0, 0);
        func_0200442c(b + 0x514, 0x4f, 0x7f, 0);
        if (func_020164a0(b + 0x334, 1) == 0x139) {
            func_02054768(b + 0xec, 0, 0);
        }
        func_02019af0(a, 0);
    }
    return 1;
}
