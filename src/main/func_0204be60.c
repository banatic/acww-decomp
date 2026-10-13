/* func_0204be60 @ 0x0204be60, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204be88(int arg);
extern int func_0204b42c(int arg);

int func_0204be60(int arg)
{
    if (func_0204be88(arg)) {
        return func_0204b42c(arg) - 0x1408;
    } else {
        return -1;
    }
}
