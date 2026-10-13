/* func_020807c0 @ 0x020807c0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02080808(void);

int func_020807c0(int param1, int param2)
{
    int result;
    int temp;

    result = 0;
    temp = func_02080808();
    if (temp != 0) {
        result = param1 + (param2 << 7);
    }
    return result;
}
