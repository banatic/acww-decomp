/* func_ov146_02299684 @ 0x02299684, 0x70 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov146_022996f4(unsigned char *, int, unsigned char, unsigned char);

void func_ov146_02299684(unsigned char *base)
{
    int i;
    for (i = 0; i < 7; i++) {
        unsigned char *p = base + i;
        int v;
        unsigned char b, byte, w, flag;
        unsigned char *q, *r;

        v = p[0xbc];
        if (v >= 32) {
            continue;
        }
        q = base + v * 35;
        b = q[0x14c];
        if (b >= 4) {
            r = base + v;
            byte = r[0x10a];
            w = (unsigned) (byte | 0x40) << 24 >> 24;
            flag = 7;
        } else {
            r = base + v;
            byte = r[0x10a];
            w = byte;
            flag = 14;
        }
        if (w != p[0xc3]) {
            func_ov146_022996f4(base, i, byte, flag);
            p[0xc3] = w;
        }
    }
}
