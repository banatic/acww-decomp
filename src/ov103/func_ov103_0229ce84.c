/* func_ov103_0229ce84 @ 0x0229ce84, 0x4c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(unsigned char *ptr, int arg);
extern void func_ov103_0229c910(unsigned char *base, int val);
extern void func_ov103_0229c994(unsigned char *base);

void func_ov103_0229ce84(unsigned char *base, int val)
{
    base[0x2da3] = (unsigned char) val;
    func_ov002_02207d24(base + 0x218c, 1);
    func_ov103_0229c910(base, val);
    if (base[0x2da0] == 1) {
        base[0x2da7] = 6;
    }
    func_ov103_0229c994(base);
}
