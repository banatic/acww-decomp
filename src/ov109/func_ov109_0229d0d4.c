/* func_ov109_0229d0d4 @ 0x0229d0d4, 0xdc bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(unsigned char *self);
extern int func_ov002_02208008(unsigned char *self);
extern void func_ov002_02207d24(unsigned char *addr, int val);
extern void func_ov002_02207d00(unsigned char *addr);

extern void func_ov109_0229cdf8(unsigned char *self);
extern int func_ov109_0229c2c4(unsigned char *self, int val);
extern void func_ov109_0229c934(unsigned char *self);
extern void func_ov109_0229c7b0(unsigned char *self);
extern int func_ov109_0229cae0(unsigned char *self, unsigned char b);
extern int func_ov109_0229ccb4(unsigned char *self, unsigned char b);
extern int func_ov109_0229cab0(unsigned char *self, unsigned char b);
extern void func_ov109_0229c418(unsigned char *self, unsigned char b, int arg);
extern void func_ov109_0229c638(unsigned char *self);
extern void func_ov109_0229c828(unsigned char *self);
extern void func_ov109_0229c4cc(unsigned char *self);

extern unsigned short data_021fbe40[];

void func_ov109_0229d0d4(unsigned char *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov109_0229cdf8(self);
        func_ov002_02207d24(self + 0x218c, 1);
        return;
    }

    {
        int r = func_ov002_02208008(self);
        if (func_ov109_0229c2c4(self, r) != 0) {
            func_ov109_0229c934(self);
            func_ov109_0229c7b0(self);
            func_ov002_02207d24(self + 0x218c, 0);
            return;
        }
    }

    if (func_ov109_0229cae0(self, self[0x29d3]) != 0) {
        // nothing
    } else {
        if ((data_021fbe40[1] & 1) != 0) {
            if (func_ov109_0229ccb4(self, self[0x29d3]) != 0) {
                if (func_ov109_0229cab0(self, self[0x29d3]) == 0) {
                    func_ov109_0229c418(self, self[0x29d3], 0);
                }
                return;
            } else {
                if (self[0x29d3] == 0xf) {
                    func_ov109_0229c638(self);
                }
                return;
            }
        }
    }

    if ((data_021fbe40[1] & 2) != 0) {
        func_ov109_0229c828(self);
        func_ov109_0229c4cc(self);
        func_ov002_02207d24(self + 0x218c, 0);
    } else {
        func_ov002_02207d00(self + 0x218c);
    }
}
