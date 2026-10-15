/* func_ov123_0229b7e4 @ 0x0229b7e4, 0xb8 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov123_0229b644(void *self);
extern char *func_ov002_02208008(void *self);
extern int func_ov002_02207fe4(void *self);
extern int func_ov002_02207fd8(void *self);
extern void func_ov123_02299c04(void *self);
extern void func_ov123_02299cc0(void *self);
extern void func_ov123_02299d00(void *self);
extern void func_ov123_0229ae84(void *self);
extern unsigned short data_021fbe40[2];

void func_ov123_0229b7e4(void *self)
{
    if (func_ov002_02208014(self)) {
        func_ov123_0229b644(self);
        return;
    } else {
        unsigned char orig = ((unsigned char *) self)[0xaa];
        func_ov002_02208008(self);
        if (func_ov002_02207fe4(self)) {
            ((unsigned char *) self)[0xaa] = 0x1f;
        } else if (func_ov002_02207fd8(self)) {
            ((unsigned char *) self)[0xaa] = 0x20;
        }
        if (orig != ((unsigned char *) self)[0xaa]) {
            func_ov123_02299c04(self);
            return;
        } else {
            unsigned short v = data_021fbe40[1];
            if (v & 1) {
                func_ov123_02299cc0(self);
            } else if (v & 2) {
                func_ov123_02299d00(self);
                ((unsigned char *) self)[0xa5] = 0x20;
                func_ov123_0229ae84(self);
            } else if (v & 8) {
                func_ov123_02299d00(self);
                ((unsigned char *) self)[0xa5] = 0x1f;
                func_ov123_0229ae84(self);
            }
        }
    }
}
