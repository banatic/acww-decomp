/* func_0200c598 @ 0x0200c598, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020112e4(void *p);
extern int func_020112d0(void *p);
extern int func_020100e8(void *p, unsigned short *t, int a, int b, int c);
void func_0200c598(unsigned char *p)
{
    unsigned char *q = p + 0x7d4;
    if (q[0xc] == 0) {
        unsigned short t;
        int a;
        int b;
        t = *(unsigned short *) q;
        a = func_020112e4(p);
        b = func_020112d0(p);
        if (func_020100e8(p, &t, a, b, 0) != 0) {
            q[0xc] = 1;
        }
    }
}
