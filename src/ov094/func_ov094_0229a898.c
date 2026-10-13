/* func_ov094_0229a898 @ 0x0229a898, 0x22 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229a888(unsigned char, unsigned char);

void func_ov094_0229a898(unsigned char r0, unsigned char r1, unsigned char r2)
{
    unsigned char r5 = r1;
    unsigned char r6 = r0;
    unsigned char r4 = r2;
    while (r5 <= r4) {
        func_ov094_0229a888(r6, r5);
        r5 = (unsigned char) (r5 + 1);
    }
}
