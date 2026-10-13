/* func_020c2c88 @ 0x020c2c88, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020c312c(int param);
extern void func_020c3690(int param, int value);

int func_020c2c88(int param)
{
    if (func_020c312c(param)) {
        func_020c3690(param, 7);
    }
    return 1;
}
