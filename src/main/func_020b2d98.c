/* func_020b2d98 @ 0x020b2d98, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b2e54(void);
extern int func_020644cc(void);
extern int func_020b2dc4(int, int, int);

int func_020b2d98(int param1, int param2)
{
    int result;
    int temp;

    if (func_020b2e54() != 0) {
        temp = func_020644cc();
        result = func_020b2dc4(param1, temp, param2);
    } else {
        result = 0;
    }
    return result;
}
