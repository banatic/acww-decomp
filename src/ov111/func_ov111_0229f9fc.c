/* func_ov111_0229f9fc @ 0x0229f9fc, 0x54 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov111_0229f504(void *s);
extern int func_ov095_0229bb94(void *p, int v);
extern int func_ov095_0229bba0(void *a, unsigned short *b, int c, int d);

int func_ov111_0229f9fc(void *s)
{
    volatile int argument_values[2];
    int v;
    int x;
    unsigned char idx;

    v = func_ov111_0229f504(s);
    if (v == 0) {
        return 0;
    }
    x = func_ov095_0229bb94((char *) s + 0xac, v);
    if (x == 0) {
        return 0;
    }
    idx = *((unsigned char *) s + 0x9e);
    return (argument_values[0] = (int) (0x10), argument_values[1] = (int) (0xa0),
            func_ov095_0229bba0((char *) s + 0xac, (unsigned short *) ((char *) s + 0x3d16), x, idx)) != 0;
}
