/* func_ov110_0229d600 @ 0x0229d600, 0x28 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov110_0229d600(void *param0);

unsigned short func_ov110_0229d600(void *param0)
{
    int r3 = 0;
    unsigned short r1 = 0x0000fff1;
    while (r3 < 15) {
        unsigned short r2 = *(unsigned short *) ((char *) param0 + (r3 << 1) + 0xb0);
        if (r2 == r1) {
            r3 += 15;
            return (unsigned char) r3;
        }
        r3++;
    }
    return 0x1f;
}
