/* func_0204bd5c @ 0x0204bd5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b268(int arg);
extern int func_0204b42c(int arg);

int func_0204bd5c(int arg)
{
    if (func_0204b268(arg) != 0) {
        return (func_0204b42c(arg) - 0x1000) >> 2;
    } else {
        return -1;
    }
}
