/* func_ov003_022177d0 @ 0x022177d0, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077978(const unsigned char *a, int c, int d);
extern unsigned short func_020778f8(const unsigned char *s);

unsigned short func_ov003_022177d0(const unsigned char *a, unsigned char *b, int c, int d, unsigned short *e)
{
    unsigned char t;
    unsigned short r;

    t = a[7];
    *b = t;
    func_02077978(a, c, d);
    r = func_020778f8(a + 5);
    *e = r;
    return r;
}
