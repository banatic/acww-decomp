/* func_02055bd8 @ 0x02055bd8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the same-arm if on an uninitialised local keeps the sign extraction as and-plus-shifts and the a2 shift late; plain expressions and bitfield unions both fold it (0x30-0x3c bytes) */

extern unsigned int func_02055bd8(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
unsigned int func_02055bd8(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
    unsigned int r0;
    unsigned int r1;
    unsigned int r2;
    unsigned int r3;
    unsigned int r4;
    unsigned int r5;
    if (r1) {
        r4 = 0x0000ffff;
        r2 = a3 & r4;
        r5 = r2 << 3;
        r0 = 0x7fff0000;
        r2 = a4;
    } else {
        r4 = 0x0000ffff;
        r2 = a3 & r4;
        r5 = r2 << 3;
        r0 = 0x7fff0000;
        r2 = a4;
    }
join:;
    r2 = r2 & r0;
    r0 = r2 >> 0x10;
    r0 = r0 << 4;
    r2 = r5 + r0;
    r0 = 0x80000000;
    r3 = a4 & r0;
    r0 = r3 >> 0x1f;
    r0 = r0 << 0x1f;
    r1 = a2 >> 4;
    r3 = r1 << 0x10;
    r1 = r2 >> 3;
    r1 = r1 & r4;
    r3 = r3 | r1;
    r0 = r0 | r3;
    return r0;
}
