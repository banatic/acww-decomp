/* func_ov120_0229a45c @ 0x0229a45c, 0x60 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229ac8c(unsigned char *p, unsigned char idx);

void func_ov120_0229a45c(unsigned char *p)
{
    unsigned char idx;
    unsigned char *base;

    idx = p[0xa3] + p[0xab] + 0xd;
    base = p + 3 * func_ov120_0229ac8c(p, idx);

    if (base[0x2745] == 0xc) {
        p[0xad] = 0x58;
        p[0xae] = 0x70;
    } else {
        p[0xad] = base[0x2743];
        p[0xae] = base[0x2744];
    }
}
