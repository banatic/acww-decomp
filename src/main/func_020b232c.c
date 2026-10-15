/* func_020b232c @ 0x020b232c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b235c(int);
extern int func_020b3fc0(int);
extern int func_020b67e8(int param);
extern int func_020b23e0(void);

int func_020b232c(int param)
{
    int r4;
    int r5;
    int result;

    r5 = param;
    r4 = func_020b3fc0((int) func_020b235c(param));
    result = func_020b67e8(r5);
    if (result != 0) {
        if (func_020b23e0() != 0) {
            return r4 + 2;
        }
    }
    return r4;
}
