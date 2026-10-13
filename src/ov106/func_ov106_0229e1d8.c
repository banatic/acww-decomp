/* func_ov106_0229e1d8 @ 0x0229e1d8, 0x104 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern void func_ov106_0229cd60(void *self, unsigned char b);
extern void func_ov106_0229cc50(void *self);
extern void func_ov106_0229c378(void *self);
extern void func_ov002_02207d24(void *p, int v);
extern int func_ov002_02208008(void *self);
extern int func_ov106_0229c4a0(void *self, int a, int b);
extern void func_ov106_0229cea8(void *self);
extern void func_ov106_0229cbdc(void *self);
extern int func_ov106_0229d3a0(void *self, unsigned char b);
extern int func_ov106_0229d390(void *self, unsigned char b);
extern int func_ov106_0229d090(void *self, unsigned char b);
extern int func_ov106_0229d0d0(void *self, unsigned char b);
extern void func_ov106_0229c9a0(void *self, unsigned char b);
extern void func_ov106_0229c958(void *self, unsigned char b);
extern void func_ov106_0229ce0c(void *self);
extern void func_ov002_02207d00(void *p);
extern unsigned short data_021fbe40[];

void func_ov106_0229e1d8(void *self)
{
    if (func_0206f56c() != 0) {
        func_ov106_0229cd60(self, ((unsigned char *) self)[0xB7]);
        func_ov106_0229cc50(self);
        func_ov106_0229c378(self);
        func_ov002_02207d24((char *) self + 0x21B8, 0);
        return;
    } else {
        if (func_ov106_0229c4a0(self, func_ov002_02208008(self), 1) != 0) {
            func_ov106_0229cea8(self);
            func_ov106_0229cbdc(self);
            func_ov002_02207d24((char *) self + 0x21B8, 0);
            return;
        } else {
            unsigned short flags = data_021fbe40[1];
            if (flags & 1) {
                if (func_ov106_0229d3a0(self, ((unsigned char *) self)[0xB8]) != 0) {
                    if (func_ov106_0229d390(self, ((unsigned char *) self)[0xB7]) != 0) {
                        if (func_ov106_0229d090(self, ((unsigned char *) self)[0xB8]) == 0) {
                            return;
                        }
                    }
                }
                if (func_ov106_0229d0d0(self, ((unsigned char *) self)[0xB8]) != 0) {
                    return;
                }
                if (func_ov106_0229d090(self, ((unsigned char *) self)[0xB8]) != 0) {
                    func_ov106_0229c9a0(self, ((unsigned char *) self)[0xB8]);
                    return;
                } else {
                    func_ov106_0229c958(self, ((unsigned char *) self)[0xB8]);
                    return;
                }
            } else {
                if (flags & 2) {
                    func_ov106_0229c9a0(self, ((unsigned char *) self)[0xB7]);
                    return;
                } else {
                    func_ov106_0229ce0c(self);
                    func_ov002_02207d00((char *) self + 0x21B8);
                }
            }
        }
    }
}
