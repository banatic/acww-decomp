/* func_02053c14 @ 0x02053c14, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int arg);
extern int func_0204bc64(int arg);
extern int func_02053c34(int);

int func_02053c14(int arg)
{
    if (func_0204bcdc(arg) != 0) {
        return func_02053c34((int) func_0204bc64(arg));
    }
    return 0;
}
