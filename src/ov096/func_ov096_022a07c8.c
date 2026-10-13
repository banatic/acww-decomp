/* func_ov096_022a07c8 @ 0x022a07c8, 0xb8 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void *p);
extern void *func_ov002_02208008(void *p);
extern int func_ov096_0229c560(void *p, void *q, int n);
extern void func_ov096_0229e898(void *p, unsigned char b, int n);
extern void func_ov096_022a18dc(void *p, int n);
extern void func_ov096_0229eb14(void *p);
extern void func_ov096_0229dd94(void *p);
extern void func_ov002_02207d24(void *p, int n);
extern int func_ov096_0229f150(void *p, unsigned char b);
extern void func_ov096_0229db78(void *p, unsigned char b);
extern void func_ov096_0229db30(void *p, unsigned char b);
extern void func_ov096_0229ea5c(void *p);
extern void func_ov002_02207d00(void *p);
extern char data_021fbe40[];

void func_ov096_022a07c8(void *self)
{
    if (func_0206f56c(self)) {
        func_ov096_0229e898(self, *((unsigned char *) self + 0xb4), 1);
        func_ov096_022a18dc(self, 7);
        return;
    } else {
        void *ret = func_ov002_02208008(self);
        if (func_ov096_0229c560(self, ret, 2)) {
            func_ov096_0229eb14(self);
            func_ov096_0229dd94(self);
            func_ov002_02207d24((char *) self + 0x2418, 0);
            return;
        } else {
            unsigned short flags = *(unsigned short *) (data_021fbe40 + 2);
            if (flags & 1) {
                if (func_ov096_0229f150(self, *((unsigned char *) self + 0xb5))) {
                    func_ov096_0229db78(self, *((unsigned char *) self + 0xb5));
                } else {
                    func_ov096_0229db30(self, *((unsigned char *) self + 0xb5));
                }
                return;
            } else if (flags & 2) {
                func_ov096_0229db78(self, *((unsigned char *) self + 0xb4));
                return;
            } else {
                func_ov096_0229ea5c(self);
                func_ov002_02207d00((char *) self + 0x2418);
                return;
            }
        }
    }
}
