/* func_ov110_0229dcc0 @ 0x0229dcc0, 0xf4 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229dcc0 {
    unsigned char pad_00[0xf4];
    unsigned char unk_F4;
    unsigned char unk_F5;
    unsigned char pad_F6[0x21f8 - 0xf6];
    unsigned char sub[0x100];
} UnkStruct_0229dcc0;

extern int func_ov110_0229e7ac(void);
extern int func_ov110_0229cce8(UnkStruct_0229dcc0 *self, unsigned char b);
extern void func_ov110_0229cbe0(UnkStruct_0229dcc0 *self);
extern int func_ov002_02207d24(void *ptr, int val);
extern void func_ov110_0229c3b8(UnkStruct_0229dcc0 *self, int val);
extern void *func_ov002_02208008(UnkStruct_0229dcc0 *self);
extern int func_ov110_0229c5a0(UnkStruct_0229dcc0 *self, void *arg, int n);
extern void func_ov110_0229ce44(UnkStruct_0229dcc0 *self);
extern void func_ov110_0229cb78(UnkStruct_0229dcc0 *self);
extern int func_ov110_0229d5e4(UnkStruct_0229dcc0 *self, unsigned char b);
extern int func_ov110_0229d5d4(UnkStruct_0229dcc0 *self, unsigned char b);
extern int func_ov110_0229d13c(UnkStruct_0229dcc0 *self, unsigned char b);
extern int func_ov110_0229d0fc(UnkStruct_0229dcc0 *self, unsigned char b);
extern void func_ov110_0229c98c(UnkStruct_0229dcc0 *self, unsigned char b);
extern void func_ov110_0229c944(UnkStruct_0229dcc0 *self, unsigned char b);
extern void func_ov110_0229cdb4(UnkStruct_0229dcc0 *self);
extern void func_ov002_02207d00(void *ptr);
extern unsigned short data_021fbe40[2];

void func_ov110_0229dcc0(UnkStruct_0229dcc0 *self)
{
    unsigned short flags;
    void *res;

    if (func_ov110_0229e7ac() != 0) {
        func_ov110_0229cce8(self, self->unk_F4);
        func_ov110_0229cbe0(self);
        func_ov002_02207d24(self->sub, 0);
        func_ov110_0229c3b8(self, 0);
        return;
    }

    res = func_ov002_02208008(self);
    if (func_ov110_0229c5a0(self, res, 1) != 0) {
        func_ov110_0229ce44(self);
        func_ov110_0229cb78(self);
        func_ov002_02207d24(self->sub, 0);
        return;
    }

    flags = data_021fbe40[1];
    if (flags & 1) {
        if (func_ov110_0229d5e4(self, self->unk_F5) == 0) {
            if (func_ov110_0229d5d4(self, self->unk_F5) == 0) {
                return;
            }
        }
        if (func_ov110_0229d13c(self, self->unk_F5) != 0) {
            return;
        }
        if (func_ov110_0229d0fc(self, self->unk_F5) != 0) {
            func_ov110_0229c98c(self, self->unk_F5);
        } else {
            func_ov110_0229c944(self, self->unk_F5);
        }
        return;
    }

    if (flags & 2) {
        func_ov110_0229c98c(self, self->unk_F4);
        return;
    }

    func_ov110_0229cdb4(self);
    func_ov002_02207d00(self->sub);
}
