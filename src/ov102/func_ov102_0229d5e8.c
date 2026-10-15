/* func_ov102_0229d5e8 @ 0x0229d5e8, 0x68 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(unsigned char *p, int v);
extern void func_ov094_022999c0(void);
extern void func_ov102_0229cc90(unsigned char *p, unsigned char v);
extern void func_ov102_0229cd38(unsigned char *p);

void func_ov102_0229d5e8(unsigned char *p, unsigned char v)
{
    p[0x25a2] = v;
    p[0x25a4] = v;
    p[0x25a3] = p[0x25aa];
    func_ov002_02207d24(p + 0x218c, 1);
    func_ov102_0229cc90(p, v);
    if (p[0x259f] == 1) {
        p[0x25a7] = 4;
    }
    func_ov102_0229cd38(p);
    func_ov094_022999c0();
}
