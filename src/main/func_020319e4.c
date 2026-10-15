/* func_020319e4 @ 0x020319e4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02031a08(int, int);
extern int func_020319ac(int, int);

int func_020319e4(int param1, int param2)
{
    int result;
    int r5 = param1;
    int r4 = param2;

    if (func_02031a08(param1, param2) != 0) {
        result = 0;
    } else {
        result = func_020319ac(r5, r4);
    }
    return result;
}
