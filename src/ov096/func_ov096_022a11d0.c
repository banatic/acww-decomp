/* func_ov096_022a11d0 @ 0x022a11d0, 0xbc bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern int func_ov096_0229c2fc(unsigned char *, int);
extern int func_ov096_0229ec4c(unsigned char *);
extern void func_ov096_0229f9dc(unsigned char *, unsigned char);
extern void func_ov096_0229cc74(unsigned char *, unsigned char, int);
extern void func_ov096_022a1a0c(unsigned char *);
extern void func_ov002_02208098(unsigned char *, int);
extern void func_ov002_02207ce4(unsigned char *, int);
extern int AOSS_FD_SET(unsigned char *);
extern void func_ov002_02207d00(unsigned char *);

void func_ov096_022a11d0(unsigned char *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov096_0229c2fc(self, 0x10000) != 0) {
            func_ov002_02208098(self, 0);
            func_ov002_02207ce4(self + 0x2418, 0x3c);
        } else {
            func_ov002_02208098(self, 3);
            func_ov096_022a1a0c(self);
        }
        return;
    }

    if (func_ov096_0229c2fc(self, 4) != 0) {
        if (func_ov096_0229ec4c(self) != 0) {
            func_ov096_0229f9dc(self, self[0xb2]);
            return;
        }
        if (func_ov096_0229c2fc(self, 0x10000) == 0) {
            if (AOSS_FD_SET(self + 0x2418) != 0) {
                if (self[0xc2] != 0) {
                    self[0xc2]--;
                    return;
                } else {
                    func_ov096_0229cc74(self, self[0xb2], 1);
                    func_ov002_02208098(self, 2);
                    return;
                }
            }
        }
    }

    func_ov002_02207d00(self + 0x2418);
}
