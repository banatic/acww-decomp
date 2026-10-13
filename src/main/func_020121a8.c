/* func_020121a8 @ 0x020121a8, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082c98(int a, int b);
extern int func_0205eac4(int a, int b);

int func_020121a8(int param0, int param1)
{
    int result;

    result = func_02082c98(param0 + 4, param1);
    if (result) {
        result = func_0205eac4(result, param1);
    }
    return result;
}
