/* func_0204ea40 @ 0x0204ea40, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204e6bc(void *p);
extern void func_02037d00(void *p);

void func_0204ea40(unsigned char *base)
{
    unsigned char *dst, *a, *b;
    int i, j;

    dst = base;
    a = base + 0x24;
    b = base + 0x2024;

    for (i = 0; i < 0x24; i++) {
        *dst++ = 0x86;
    }

    for (j = 0; j < 0x10; j++) {
        func_0204e6bc(a);
        func_02037d00(b);
        a += 0x200;
        b += 0x20;
    }

    *(base + 0x2224) &= ~3;
}
