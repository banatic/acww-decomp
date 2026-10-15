/* func_ov105_0229e230 @ 0x0229e230, 0x90 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];
extern int func_ov002_02208014(void);
extern void func_ov105_0229cbb0(unsigned char *self);
extern int func_ov002_02208008(unsigned char *self);
extern int func_ov105_0229c340(unsigned char *self, int arg);
extern int func_ov002_02209044(unsigned char *a, int b, unsigned char *c, unsigned char d);
extern void func_ov105_0229cebc(unsigned char *self);
extern void func_ov002_0220a1dc(unsigned char *a);
extern unsigned char *func_ov002_02208098(unsigned char *self, unsigned char value);
extern void func_ov105_0229ce54(unsigned char *self);

void func_ov105_0229e230(unsigned char *self)
{
    int r4;
    unsigned char d;
    if (func_ov002_02208014() != 0) {
        func_ov105_0229cbb0(self);
        return;
    }
    r4 = func_ov002_02208008(self);
    d = (unsigned char) func_ov105_0229c340(self, 0x800);
    if (func_ov002_02209044(self + 0x2508, r4, self + 0x2bf, d) != 0) {
        func_ov105_0229cebc(self);
        return;
    }
    if (data_021fbe40[1] & 1) {
        func_ov002_0220a1dc(self + 0x24a4);
        func_ov002_02208098(self, 0xc);
    } else if (data_021fbe40[1] & 2) {
        func_ov105_0229ce54(self);
    }
}
