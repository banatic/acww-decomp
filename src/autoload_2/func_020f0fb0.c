/* func_020f0fb0 @ 0x020f0fb0, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020f5a4c(unsigned char *, int);
extern void func_020f5b04(int, int);

void func_020f0fb0(unsigned char *p, int arg)
{
    if (p[0x72] != 0) {
        p[0x72] = p[0x72] - 1;
        return;
    } else {
        if (p[0x72] != 0) {
            return;
        }
        func_020f5b04(func_020f5a4c(p, arg), arg);
    }
}
