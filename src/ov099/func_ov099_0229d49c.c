/* func_ov099_0229d49c @ 0x0229d49c, 0x7c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov099_0229c470(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov002_02209044(void *p1, int p2, void *p3, int p4);
extern void func_ov099_0229c688(void *self);
extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern unsigned short data_021fbe40[];

void func_ov099_0229d49c(void *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov099_0229c470(self);
        return;
    }
    {
        int result = func_ov002_02208008(self);
        if (func_ov002_02209044((char *) self + 0x22d8, result, (char *) self + 0x290c, 0) != 0) {
            func_ov099_0229c688(self);
            return;
        }
    }
    {
        unsigned short flag = data_021fbe40[1];
        if (flag & 1) {
            func_ov002_0220a1dc((char *) self + 0x2274);
            func_ov002_02208098(self, 7);
            return;
        }
        if (flag & 2) {
            func_ov099_0229c470(self);
            return;
        }
    }
}
