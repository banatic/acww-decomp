/* func_ov100_0229e124 @ 0x0229e124, 0x58 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov002_02208098(unsigned char *p, int n);
extern void func_ov002_02207ce4(unsigned char *p, int n);
extern int func_ov100_0229c2c0(unsigned char *p, int n);
extern int func_ov100_0229cfd0(unsigned char *p);
extern void func_ov100_0229d7d8(unsigned char *p, unsigned char c);
extern void func_ov002_02207d00(unsigned char *p);

void func_ov100_0229e124(unsigned char *p)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(p, 0);
        func_ov002_02207ce4(p + 0x218c, 0x3c);
    } else {
        if (func_ov100_0229c2c0(p, 4) != 0 && func_ov100_0229cfd0(p) != 0) {
            func_ov100_0229d7d8(p, p[0x291e]);
        } else {
            func_ov002_02207d00(p + 0x218c);
        }
    }
}
