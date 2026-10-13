/* func_ov113_0229a1b8 @ 0x0229a1b8, 0xbc bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9b];
    unsigned char unk_9B;
} UnkStruct_0229a1b8;

extern int func_ov002_02208014(UnkStruct_0229a1b8 *self);
extern int func_ov002_02208008(UnkStruct_0229a1b8 *self);
extern int func_ov113_02299644(UnkStruct_0229a1b8 *self, int arg);
extern void func_ov113_0229a108(UnkStruct_0229a1b8 *self);
extern void func_ov113_0229990c(UnkStruct_0229a1b8 *self);
extern void func_ov113_022998ec(UnkStruct_0229a1b8 *self);
extern void func_ov113_02299980(UnkStruct_0229a1b8 *self);
extern int func_ov113_02299aa4(UnkStruct_0229a1b8 *self);
extern unsigned short data_021fbe40[2];

void func_ov113_0229a1b8(UnkStruct_0229a1b8 *self)
{
    unsigned short v;

    if (func_ov002_02208014(self) != 0) {
        func_ov113_0229a108(self);
        return;
    }

    if (func_ov113_02299644(self, func_ov002_02208008(self)) != 0) {
        func_ov113_0229990c(self);
        return;
    }

    v = data_021fbe40[1];

    if (v & 1) {
        func_ov113_022998ec(self);
        return;
    }

    if (v & 2) {
        self->unk_9B = 3;
        func_ov113_02299980(self);
        func_ov113_02299aa4(self);
        return;
    }

    if (v & 0x200) {
        self->unk_9B = 5;
        if (func_ov113_02299aa4(self) != 0) {
            func_ov113_02299980(self);
        }
        return;
    }

    if (v & 0x100) {
        self->unk_9B = 4;
        if (func_ov113_02299aa4(self) != 0) {
            func_ov113_02299980(self);
        }
        return;
    }
}
