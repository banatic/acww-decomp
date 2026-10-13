/* func_0208a20c @ 0x0208a20c, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a160(int arg);

int func_0208a20c(int arg)
{
    if (func_0208a160(arg + 0xC) && func_0208a160(arg + 0x20)) {
        return 1;
    } else {
        return 0;
    }
}
