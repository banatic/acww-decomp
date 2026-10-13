/* func_020539e4 @ 0x020539e4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int);
extern int func_0204bc64(int);
extern int func_02053a04(int);

int func_020539e4(int arg0)
{
    if (func_0204bcdc(arg0) != 0) {
        return func_02053a04(func_0204bc64(arg0));
    }
    return 0;
}
