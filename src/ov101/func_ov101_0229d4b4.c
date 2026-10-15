/* func_ov101_0229d4b4 @ 0x0229d4b4, 0xf4 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40[2];
extern int func_ov002_02208014(void);
extern void func_ov101_0229cfd4(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov101_0229c2c0(void *self, int arg);
extern void func_ov101_0229ca58(void *self);
extern void func_ov101_0229c7d0(void *self);
extern int func_ov002_02207d24(void *p, int v);
extern int func_ov101_0229cc50(void *self, unsigned char b);
extern int func_ov101_0229ce38(void *self, unsigned char b);
extern int func_ov101_0229cc20(void *self, unsigned char b);
extern void func_ov101_0229c42c(void *self, unsigned char b, int c);
extern void func_ov101_0229c660(void *self);
extern void func_ov101_0229c844(void *self);
extern void *func_ov002_0220a720(void *p, int v);
extern unsigned char *func_ov002_02208098(void *self, unsigned char value);
extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_02207d00(void *p);

struct UnkStruct_0229d4b4 {
    char pad_00[0xb3];
    unsigned char unk_B3;
    char pad_B4[0x21b4 - 0xb4];
    unsigned int unk_21B4;
    char pad_21B8[0x2810 - 0x21b8];
    unsigned int unk_2810;
};

void func_ov101_0229d4b4(struct UnkStruct_0229d4b4 *self)
{
    if (func_ov002_02208014() != 0) {
        func_ov101_0229cfd4(self);
        func_ov002_02207d24(&self->unk_21B4, 1);
        return;
    }

    {
        int arg = func_ov002_02208008(self);
        if (func_ov101_0229c2c0(self, arg) != 0) {
            func_ov101_0229ca58(self);
            func_ov101_0229c7d0(self);
            func_ov002_02207d24(&self->unk_21B4, 0);
            return;
        }

        if (func_ov101_0229cc50(self, self->unk_B3) == 0 && (data_021fbe40[1] & 1) != 0) {
            if (func_ov101_0229ce38(self, self->unk_B3) != 0) {
                if (func_ov101_0229cc20(self, self->unk_B3) == 0) {
                    func_ov101_0229c42c(self, self->unk_B3, 0);
                    return;
                } else {
                    return;
                }
            } else {
                if (self->unk_B3 == 0xf) {
                    func_ov101_0229c660(self);
                    return;
                } else {
                    return;
                }
            }
        } else {
            if ((data_021fbe40[1] & 2) != 0) {
                func_ov101_0229c844(self);
                func_ov002_0220a720(&self->unk_2810, 9);
                func_ov002_02208098(self, 0x17);
                RtcSendPxiCommand(0x28);
                func_ov002_02207d24(&self->unk_21B4, 0);
                return;
            } else {
                func_ov002_02207d00(&self->unk_21B4);
                return;
            }
        }
    }
}
