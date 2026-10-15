/* func_ov107_0229d828 @ 0x0229d828, 0xe0 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(unsigned char *self);
extern int func_ov002_02207d24(unsigned char *addr, int val);
extern void func_ov002_02207d00(unsigned char *addr);

extern void func_ov107_0229d4d4(unsigned char *self);
extern int func_ov107_0229c824(unsigned char *self, int val);
extern void func_ov107_0229cf90(unsigned char *self);
extern void func_ov107_0229ce1c(unsigned char *self);
extern int func_ov107_0229d15c(unsigned char *self, unsigned char b);
extern int func_ov107_0229d388(unsigned char *self, unsigned char b);
extern int func_ov107_0229d128(unsigned char *self, unsigned char b);
extern void func_ov107_0229c990(unsigned char *self, unsigned char b, int arg);
extern void func_ov107_0229cca8(unsigned char *self);
extern void func_ov107_0229ce90(unsigned char *self);
extern void func_ov107_0229cb14(unsigned char *self);

extern unsigned short data_021fbe40[];

void func_ov107_0229d828(unsigned char *self)
{
    if (func_ov002_02208014(self) != 0) {
        func_ov107_0229d4d4(self);
        func_ov002_02207d24(self + 0x21cc, 1);
        return;
    }

    {
        int r = func_ov002_02208008(self);
        if (func_ov107_0229c824(self, r) != 0) {
            func_ov107_0229cf90(self);
            func_ov107_0229ce1c(self);
            func_ov002_02207d24(self + 0x21cc, 0);
            return;
        }
    }

    if (func_ov107_0229d15c(self, self[0xb8]) != 0) {
        // nothing
    } else {
        if ((data_021fbe40[1] & 1) != 0) {
            if (func_ov107_0229d388(self, self[0xb8]) != 0) {
                if (func_ov107_0229d128(self, self[0xb8]) == 0) {
                    func_ov107_0229c990(self, self[0xb8], 0);
                }
                return;
            } else {
                if (self[0xb8] == 0xf) {
                    func_ov107_0229cca8(self);
                }
                return;
            }
        }
    }

    if ((data_021fbe40[1] & 2) != 0) {
        func_ov107_0229ce90(self);
        func_ov107_0229cb14(self);
        func_ov002_02207d24(self + 0x21cc, 0);
    } else {
        func_ov002_02207d00(self + 0x21cc);
    }
}
