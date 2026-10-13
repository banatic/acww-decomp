/* func_020a1c9c @ 0x020a1c9c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a1c90(int);
extern void func_020a1bd0(int);
extern int func_020a16e0(void);

int func_020a1c9c(void)
{
    int a = func_020a1c90(0);
    int b = func_020a1c90(1);
    if (a == 1 || b == 1) {
        return 1;
    }
    if (a != 0 && b != 0) {
        return 4;
    }
    if (a != 0) {
        func_020a1bd0(1);
    } else {
        if (b != 0) {
            func_020a1bd0(0);
        } else {
            func_020a1bd0(func_020a16e0());
        }
    }
    return 0;
}
