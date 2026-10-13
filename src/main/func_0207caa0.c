/* func_0207caa0 @ 0x0207caa0, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200363c(int, unsigned int *);

int func_0207caa0(int a, unsigned int *b)
{
    if (func_0200363c(a, b) != 0) {
        if ((b[a >> 5] >> (a & 31)) & 1) {
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}
