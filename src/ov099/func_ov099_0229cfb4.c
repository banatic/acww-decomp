/* func_ov099_0229cfb4 @ 0x0229cfb4, 0x50 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(unsigned char *addr, int v);
extern void func_ov099_0229c880(unsigned char *base, int value);
extern void func_ov099_0229c928(unsigned char *base);

void func_ov099_0229cfb4(unsigned char *base, int value)
{
    unsigned char b;

    base[0x2906] = value;
    func_ov002_02207d24(base + 0x218c, 1);
    func_ov099_0229c880(base, value);

    b = base[0x2903];
    if (b == 1) {
        // empty
    } else if (b == 2) {
        base[0x290a] = 5;
    }

    func_ov099_0229c928(base);
}
