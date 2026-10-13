/* func_02068f2c @ 0x02068f2c, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02068f2c(unsigned short **p, int a, int b)
{
    unsigned int mask;
    int y, x;
    unsigned short v;

    if (b) {
        mask = 0xb000;
    } else {
        if (a != 0) {
            goto L_mask2000;
        }
        mask = 0x1000;
        goto L_mask_end;
    L_mask2000:
        mask = 0x2000;
    L_mask_end:;
    }

    if (mask == 0x1000) {
        return;
    }

    for (y = 0xd; y <= 0x10; y++) {
        for (x = 3; x <= 0xe; x++) {
            v = *(*p + y * 32 + x);
            if ((v & 0xf000) == 0x1000) {
                *(*p + y * 32 + x) = (unsigned short) (v & 0xffff0fff) | mask;
            }
        }
    }
}
