/* func_02053990 @ 0x02053990, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int);
extern int func_0204bc64(int);
extern int func_020539b0(int);

int func_02053990(int arg)
{
    if (func_0204bcdc(arg)) {
        return func_020539b0(func_0204bc64(arg));
    }
    return 0;
}
