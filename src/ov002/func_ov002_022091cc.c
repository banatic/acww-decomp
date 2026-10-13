/* func_ov002_022091cc @ 0x022091cc, 0x114 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_022091cc {
    u8 pad_00[0x16];
    u8 unk_16;
    u8 unk_17;
    u8 pad_18[2];
    u8 unk_1A;
    u8 pad_1B[4];
    u8 unk_1F;
};

extern void func_ov002_02208df8(struct UnkStruct_022091cc *self);
extern int func_ov002_02208a14(struct UnkStruct_022091cc *self, int bit);
extern void func_ov002_02208a04(struct UnkStruct_022091cc *self, int bit);
extern void func_ov002_02209b94(char *p, int i);
extern void func_02070a04(char *p, int a, int b);
extern void func_ov002_0220968c(struct UnkStruct_022091cc *self, int v);
extern void func_ov002_02208d74(struct UnkStruct_022091cc *self);
extern void func_0200277c(int v);
extern void func_ov002_02209518(struct UnkStruct_022091cc *self);
extern void func_ov002_022094b4(struct UnkStruct_022091cc *self);
extern void func_ov002_02209398(struct UnkStruct_022091cc *self);
extern void func_ov002_0220932c(struct UnkStruct_022091cc *self);

void func_ov002_022091cc(struct UnkStruct_022091cc *self)
{
    func_ov002_02208df8(self);
    if (func_ov002_02208a14(self, 8)) {
        func_ov002_02208a04(self, 8);
        func_ov002_02209b94((char *) self + 0x28 + self->unk_1F * 0x74, 0xf);
        func_02070a04((char *) self + 0x28 + self->unk_1F * 0x74, 0, 1);
    }
    switch (self->unk_17) {
        case 1:
            switch (self->unk_16) {
                case 0:
                    func_ov002_0220968c(self, 1);
                    self->unk_17 = 0;
                    func_ov002_02208d74(self);
                    break;
                case 1:
                case 2:
                    self->unk_17 = 0;
                    break;
                case 3:
                    func_ov002_0220968c(self, 4);
                    break;
            }
            break;
        case 2:
            switch (self->unk_16) {
                case 3:
                    func_ov002_0220968c(self, 4);
                    self->unk_17 = 0;
                    break;
                case 1:
                    func_0200277c(self->unk_1A);
                    func_ov002_0220968c(self, 0);
                    self->unk_17 = 0;
                    break;
                case 0:
                case 2:
                    self->unk_17 = 0;
                    break;
            }
            break;
    }
    switch (self->unk_16) {
        case 0:
        case 3:
            break;
        case 1:
            func_ov002_02209518(self);
            break;
        case 4:
            func_ov002_022094b4(self);
            break;
        case 2:
            func_ov002_02209398(self);
            break;
        case 5:
            func_ov002_0220932c(self);
            break;
    }
}
