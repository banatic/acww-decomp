/* func_0209bf28 @ 0x0209bf28, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_0209c410(unsigned char *p, unsigned char c);
extern int func_020644cc(int n);
extern void func_0209c448(unsigned char *p, unsigned char a, unsigned char b);

int func_0209bf28(unsigned char *base, short *arr)
{
    int found = 0;
    int idx;
    int v;

    for (idx = 0; idx < 8; idx++) {
        if (func_0209c410(base + 0x11, idx) < 0xff) {
            v = func_020644cc(10);
            if (v > 0) {
                func_0209c448(base + 0x11, idx, (*arr * v) >> 12);
            }
            found = 1;
        }
        arr++;
    }
    return found;
}
