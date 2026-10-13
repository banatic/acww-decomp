/* func_020536c8 @ 0x020536c8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(int arg);
extern int func_0204bc64(int arg);
extern int func_020536e8(int arg);

int func_020536c8(int arg)
{
    if (func_0204bcdc(arg) != 0) {
        return func_020536e8(func_0204bc64(arg));
    }
    return 0;
}
