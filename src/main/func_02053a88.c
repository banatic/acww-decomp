/* func_02053a88 @ 0x02053a88, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int arg);
extern int func_0204bc64(int arg);
extern int func_02053aa8(int arg);

int func_02053a88(int arg)
{
    if (func_0204bcdc(arg)) {
        return func_02053aa8(func_0204bc64(arg));
    } else {
        return 0;
    }
}
