/* func_02053c68 @ 0x02053c68, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int);
extern int func_0204bc64(int);
extern int func_02053c88(int);

int func_02053c68(int arg)
{
    if (func_0204bcdc(arg)) {
        return func_02053c88(func_0204bc64(arg));
    }
    return 0;
}
