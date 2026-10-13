/* func_ov110_0229c944 @ 0x0229c944, 0x48 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *ptr, int x);
extern void func_ov002_0220a374(void *ptr, int x);
extern void func_ov002_02208098(void *ptr, int x);

void func_ov110_0229c944(unsigned char *base, unsigned char param)
{
    unsigned char *src;
    unsigned char *dst;
    unsigned char *p;
    unsigned char val;

    func_ov002_02207d24(base + 0x21f8, 1);
    src = base + 0x8d;
    val = *src;
    dst = base + 0xf8;
    *dst = val;
    p = base + 0xf7;
    *p = param;
    func_ov002_0220a374(base + 0x22e0, 6);
    func_ov002_02208098(base, 14);
}
