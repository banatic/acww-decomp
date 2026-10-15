/* func_ov105_0229eb54 @ 0x0229eb54, 0xe8 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x94];
    s32 unk_94; // 0x94
    u8 pad_98[0x21c];
    u8 unk_2B4; // 0x2b4
    u8 pad_2B5[1];
    u8 unk_2B6; // 0x2b6
    u8 pad_2B7[3];
    u8 unk_2BA; // 0x2ba
    u8 pad_2BB[5];
    u8 unk_2C0; // 0x2c0
    u8 pad_2C1[2];
    u8 unk_2C3; // 0x2c3
    u8 pad_2C4[0x38];
    u8 unk_2FC; // 0x2fc
    u8 pad_2FD[0xa5f];
    u8 unk_D5C; // 0xd5c
    u8 pad_D5D[0x27];
    u8 unk_D84; // 0xd84
    u8 pad_D85[0x1707];
    u8 unk_248C; // 0x248c
    u8 pad_248D[0x7b];
    u8 unk_2508; // 0x2508
    u8 pad_2509[0x50f];
    u8 unk_2A18; // 0x2a18
    u8 pad_2A19[0x39f];
    u8 arr[50][0x100]; // 0x2db8
} UnkStruct_0229eb54;

extern void func_ov094_0229af40(void *, int);
extern void func_ov094_0229bbd8(void *, int);
extern void func_ov094_0229a2b0(void *, int);
extern void func_ov002_02209e18(void *);
extern void func_ov002_02209984(void *, int, int, int);
extern void func_0206e2ec(void *, int);
extern void func_02066650(void *);
extern int func_02066830(void *, const void *);
extern int func_020984e8(void);
extern int func_020989e0(int object);
extern void *func_02097f58(int, int);
extern void func_ov105_0229c694(UnkStruct_0229eb54 *);

void func_ov105_0229eb54(UnkStruct_0229eb54 *self)
{
    int i;
    int r;
    u8 *src;

    self->unk_94 = 0;
    func_ov094_0229af40(&self->unk_2FC, 2);
    func_ov094_0229bbd8(&self->unk_D5C, 1);
    func_ov094_0229a2b0(&self->unk_D84, 6);
    self->unk_2B6 = 0x40;
    func_ov002_02209e18(&self->unk_248C);
    self->unk_2B4 = 0;
    self->unk_2BA = 0x1a;
    func_ov002_02209984(&self->unk_2508, 3, 0, 0);
    func_0206e2ec(&self->unk_2A18, 3);
    self->unk_2C0 = 0;

    for (i = 0; i < 50; i++) {
        func_02066650(&self->arr[i]);
    }

    r = func_020989e0(func_020984e8());
    if (r != 0) {
        src = (u8 *) func_02097f58(r, 0);
        for (i = 0; i < 50; i++) {
            func_02066830(&self->arr[i], src);
            src += 0x100;
        }
    }

    func_ov105_0229c694(self);
    self->unk_2C3 = 0;
}
