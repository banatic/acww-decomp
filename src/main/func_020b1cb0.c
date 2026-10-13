/* func_020b1cb0 @ 0x020b1cb0, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02030890(int param);
extern int func_020b65c4(void);
extern int func_020b6744(void);
extern int func_020b67e8(int x);
extern int func_020b67c0(int x);
extern int func_020b66ec(int x);
extern int func_020b1d2c(int param);
extern void func_020b1d18(int arg);

void func_020b1cb0(int param)
{
    if (func_02030890(param) == -1) {
        goto tail;
    }
    {
        int a = func_020b65c4();
        if (func_020b6744() != 0) {
            func_020b1d18(5);
            return;
        }
        if (func_020b67e8(a) != 0 || func_020b67c0(a) != 0) {
            func_020b1d18(6);
            return;
        }
        if (func_020b66ec(a) != 0) {
            func_020b1d18(5);
            return;
        }
    }
tail:
    func_020b1d18(func_020b1d2c(param));
}
