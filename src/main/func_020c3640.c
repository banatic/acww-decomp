/* func_020c3640 @ 0x020c3640, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(void);
extern void func_020c3690(int param1, int param2);

int func_020c3640(int param1)
{
    int r4;
    int result;

    r4 = param1;
    result = func_020b65c4();
    if (result == 0) {
        func_020c3690(r4, 7);
    }
    return 1;
}
