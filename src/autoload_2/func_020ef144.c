/* func_020ef144 @ 0x020ef144, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020ef8bc(unsigned char *p);
extern void func_020ef1f8(unsigned char *self, int i, int arg);

void func_020ef144(unsigned char *self, int arg)
{
    int i;
    unsigned char *p;

    i = 0;
    if ((int) self[0x36] > 0) {
        p = self + 8;
        do {
            if (func_020ef8bc(p) != 0) {
                func_020ef1f8(self, i, arg);
            }
            i = i + 1;
            p = p + 0xc;
        } while (i < (int) self[0x36]);
    }
}
