/* func_ov108_0229d418 @ 0x0229d418, 0x9c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208008(void *self);
extern int func_ov108_0229c2f0(void *self, int a, int b);
extern void func_ov108_0229c9d8(void *self);
extern void func_ov108_0229c72c(void *self);
extern int func_ov108_0229cb54(void *self, unsigned char byte);
extern void func_ov108_0229c578(void *self, unsigned char byte);
extern void func_ov108_0229c52c(void *self, unsigned char byte);
extern void func_ov108_0229c940(void *self);
extern int func_ov002_02207d24(void *ptr, int zero);
extern void func_ov002_02207d00(void *ptr);

extern struct {
    unsigned short field0;
    unsigned short field2;
} data_021fbe40;

void func_ov108_0229d418(unsigned char *self)
{
    if (func_ov108_0229c2f0(self, func_ov002_02208008(self), 1) != 0) {
        func_ov108_0229c9d8(self);
        func_ov108_0229c72c(self);
        func_ov002_02207d24(self + 0x23b0, 0);
    } else {
        unsigned short flags = data_021fbe40.field2;
        if (flags & 1) {
            if (func_ov108_0229cb54(self, self[0x2b0]) != 0) {
                func_ov108_0229c578(self, self[0x2b0]);
            } else {
                func_ov108_0229c52c(self, self[0x2b0]);
            }
        } else if (flags & 2) {
            func_ov108_0229c578(self, self[0x2af]);
        } else {
            func_ov108_0229c940(self);
            func_ov002_02207d00(self + 0x23b0);
        }
    }
}
