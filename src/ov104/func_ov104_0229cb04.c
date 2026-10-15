/* func_ov104_0229cb04 @ 0x0229cb04, 0x34 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d938(unsigned char *p1, unsigned char p2, unsigned char *p3);

void func_ov104_0229cb04(unsigned char *base)
{
    unsigned char idx;
    int i;

    i = 0;
    idx = 0x0b;

    do {
        func_ov104_0229d938(base, idx, base + 0x37b4 + (i << 8));
        i++;
        idx = (unsigned char) (idx + 1);
    } while (idx <= 0x14);
}
