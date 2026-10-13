/* func_ov101_0229d720 @ 0x0229d720, 0xa0 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;

extern int func_ov101_0229cc50(void *self, unsigned char b);
extern void func_ov002_02208098(void *self, int v);
extern void func_ov002_02207ce4(void *sub, int v);
extern int AOSS_FD_SET(void *sub);
extern void func_ov101_0229dbb0(void *self);
extern void func_ov101_0229c42c(void *self, unsigned char b, int v);
extern void func_ov002_02207d00(void *sub);

typedef struct {
    unsigned char pad_00[0xb0];
    unsigned char b0;                    // 0xb0
    unsigned char pad_B1[8];             // 0xb1..0xb8
    unsigned char b9;                    // 0xb9
    unsigned char pad_BA[0x21b4 - 0xba]; // 0xba..0x21b3
} UnkStruct_0229d720;

void func_ov101_0229d720(UnkStruct_0229d720 *self)
{
    if (data_021fbdd8 == 0) {
        if (func_ov101_0229cc50(self, self->b0) != 0) {
            func_ov002_02208098(self, 0);
            func_ov002_02207ce4((char *) self + 0x21b4, 0x3c);
            return;
        } else {
            func_ov002_02208098(self, 3);
            func_ov101_0229dbb0(self);
            return;
        }
    } else {
        if (func_ov101_0229cc50(self, self->b0) == 0) {
            if (AOSS_FD_SET((char *) self + 0x21b4) != 0) {
                if (self->b9 != 0) {
                    self->b9--;
                    return;
                } else {
                    func_ov101_0229c42c(self, self->b0, 1);
                    func_ov002_02208098(self, 2);
                    return;
                }
            }
        }
        func_ov002_02207d00((char *) self + 0x21b4);
    }
}
