/* func_ov101_0229d410 @ 0x0229d410, 0xa4 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208008(void *self);
extern int func_ov101_0229c2c0(void *self, int arg);
extern void func_ov101_0229ca58(void *self);
extern void func_ov101_0229c7d0(void *self);
extern void func_ov002_02207d24(void *ptr, int val);
extern int func_ov101_0229ce38(void *self, unsigned char byte);
extern int func_ov101_0229cc20(void *self, unsigned char byte);
extern void func_ov101_0229c624(void *self, unsigned char byte);
extern void func_ov101_0229c5dc(void *self, unsigned char byte);
extern void func_ov101_0229ca00(void *self);
extern void func_ov002_02207d00(void *ptr);
extern unsigned short data_021fbe40[];

void func_ov101_0229d410(void *self)
{
    unsigned short flags;

    if (func_ov101_0229c2c0(self, func_ov002_02208008(self)) != 0) {
        func_ov101_0229ca58(self);
        func_ov101_0229c7d0(self);
        func_ov002_02207d24((char *) self + 0x21b4, 0);
        return;
    }

    flags = data_021fbe40[1];

    if (flags & 1) {
        if (func_ov101_0229ce38(self, *((unsigned char *) self + 0xb3)) != 0) {
            if (func_ov101_0229cc20(self, *((unsigned char *) self + 0xb3)) != 0) {
                func_ov101_0229c624(self, *((unsigned char *) self + 0xb3));
            } else {
                func_ov101_0229c5dc(self, *((unsigned char *) self + 0xb3));
            }
        } else {
            return;
        }
    } else if (flags & 2) {
        func_ov101_0229c624(self, *((unsigned char *) self + 0xb2));
    } else {
        func_ov101_0229ca00(self);
        func_ov002_02207d00((char *) self + 0x21b4);
    }
}
