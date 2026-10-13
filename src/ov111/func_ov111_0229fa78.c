/* func_ov111_0229fa78 @ 0x0229fa78, 0x54 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov111_0229f504(void *s);
extern int func_ov095_0229bb98(void *p, int v);
extern int func_ov095_0229bba0(void *a, unsigned short *b, int c, int d, int e, int f);

int func_ov111_0229fa78(void *s)
{
    int v;
    int x;
    unsigned char idx;

    v = func_ov111_0229f504(s);
    if (v == 0) {
        return 0;
    }
    x = func_ov095_0229bb98((char *) s + 0xac, v);
    if (x == 0) {
        return 0;
    }
    idx = *((unsigned char *) s + 0x9e);
    return func_ov095_0229bba0((char *) s + 0xac, (unsigned short *) ((char *) s + 0x3d16), x, idx, 0x10, 0xa0) != 0;
}
