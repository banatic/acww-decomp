/* func_ov105_0229e860 @ 0x0229e860, 0xac bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern int func_ov105_0229c340(unsigned char *self, int a);
extern void func_ov002_02208098(unsigned char *self, int a);
extern void func_ov105_0229f25c(unsigned char *self);
extern void func_ov002_02207ce4(unsigned char *self, int a);
extern int func_ov105_0229d310(unsigned char *self);
extern void func_ov105_0229d970(unsigned char *self, unsigned char a);
extern int AOSS_FD_SET(unsigned char *self);
extern void func_ov105_0229cadc(unsigned char *self, unsigned char a, int b);
extern void func_ov002_02207d00(unsigned char *self);

void func_ov105_0229e860(unsigned char *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov105_0229c340(self, 4) != 0) {
            func_ov002_02208098(self, 3);
            func_ov105_0229f25c(self);
        } else {
            func_ov002_02208098(self, 0);
            func_ov002_02207ce4(self + 0x23bc, 0x3c);
        }
    } else {
        if (func_ov105_0229c340(self, 4) != 0) {
            if (func_ov105_0229d310(self) != 0) {
                func_ov105_0229d970(self, self[0x2b5]);
                return;
            } else {
                if (AOSS_FD_SET(self + 0x23bc) != 0) {
                    if (self[0x2c3] != 0) {
                        self[0x2c3]--;
                    } else {
                        func_ov105_0229cadc(self, self[0x2b5], 1);
                        func_ov002_02208098(self, 2);
                    }
                    return;
                }
            }
        }
        func_ov002_02207d00(self + 0x23bc);
    }
}
