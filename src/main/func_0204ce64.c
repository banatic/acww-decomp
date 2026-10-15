/* func_0204ce64 @ 0x0204ce64, 0xa6 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00;              // 0x00
    u8 unk_01;              // 0x01
    u8 unk_02;              // 0x02
    u8 pad_03;              // 0x03
    u32 unk_04;             // 0x04
    u8 pad_08[0x21 - 0x08]; // 0x08..0x20
    s8 unk_21;              // 0x21
    u8 unk_22;              // 0x22
    u8 pad_23[0x54 - 0x23]; // 0x23..0x53
    u8 unk_54;              // 0x54
    u8 unk_55;              // 0x55
    u8 unk_56;              // 0x56
    u8 unk_57;              // 0x57
    u8 arr[16];             // 0x58..0x67
    u8 unk_68;              // 0x68
    u8 unk_69;              // 0x69
    u8 unk_6A;              // 0x6a
    u8 unk_6B;              // 0x6b
} UnkStruct_0204ce64;

extern void func_0209df64(UnkStruct_0204ce64 *self);
extern u32 func_020644cc(int value);
extern int func_0209de88(int a, int b, int c);
extern void func_0204cc34(UnkStruct_0204ce64 *a, UnkStruct_0204ce64 *b);
extern void func_0204cc24(UnkStruct_0204ce64 *self);
extern void func_0204cc14(UnkStruct_0204ce64 *self);
extern void func_0204cd20(UnkStruct_0204ce64 *self);
extern void func_0204cc98(UnkStruct_0204ce64 *self);
extern void func_0204cbe0(UnkStruct_0204ce64 *self);
extern void func_020467cc(void);

void func_0204ce64(UnkStruct_0204ce64 *self)
{
    u8 *p;
    int i;

    func_0209df64(self);
    self->unk_04 = func_020644cc(5);
    func_0209de88(self->unk_02, self->unk_01, self->unk_00);
    func_0204cc34(self, self);
    func_0204cc24(self);
    func_0204cc14(self);
    func_0204cd20(self);
    func_0204cc98(self);
    func_0204cbe0(self);

    p = self->arr;
    for (i = 0; i < 4; i++) {
        p[0] = 1;
        p[1] = 1;
        p[2] = 0;
        p[3] = 0;
        p += 4;
    }

    self->unk_21 = -1;
    self->unk_54 = 1;
    self->unk_55 = 1;
    self->unk_56 = 0;
    self->unk_57 = 0;

    func_020467cc();

    self->unk_6B = 0;
    self->unk_6A = 0xFF;
    self->unk_69 = 0xFF;
    self->unk_68 = 0xFF;
    self->unk_22 = 0;
}
