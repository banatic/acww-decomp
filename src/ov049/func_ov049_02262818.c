/* func_ov049_02262818 @ 0x02262818, 0xc8 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov049_0226048c(void *p);
extern int func_ov049_02260500(void *p);
extern void *func_02095794(int n);
extern void func_0201b458(void *dst, void *src, void *data);
extern int func_0201c378(void *p, int n);
extern int func_0201c2c8(void *p, int n);
extern int func_020e8b4c(int a, int b);
extern void *data_021c80bc;
extern int func_0204ed30(void *a, void *b);
extern int func_020eaa2c(void *a, void *b);
extern void func_ov049_02262a94(void *p, int n);
extern void func_0201aff4(void *a, int b);
extern int func_02019e00(void *a);
extern int func_02019de8(void *a);

typedef struct UnkStruct_02262818 {
    u8 pad_00[0x5c];
    u8 unk_5C[0x8e - 0x5c];
    s16 unk_8E;
    u8 pad_90[0x350 - 0x90];
    u8 unk_350[0x564 - 0x350];
    u8 unk_564[1];
} UnkStruct_02262818;

int func_ov049_02262818(UnkStruct_02262818 *self)
{
    u32 arr[3];
    u32 buf[3];
    int r6, r4;

    if (func_ov049_0226048c(self) != 0) {
        return 1;
    }
    if (func_ov049_02260500(self) != 0) {
        return 1;
    }

    {
        u32 *p = func_02095794(4);
        arr[0] = p[0];
        arr[1] = p[1];
        arr[2] = p[2];
    }
    func_0201b458(buf, self, arr);
    r6 = func_0201c378(self, 4);
    r4 = func_0201c2c8(self, 4);
    func_020e8b4c(self->unk_8E, r4);
    func_0204ed30(data_021c80bc, self->unk_5C);

    if (r6 > 0x5000) {
        if (func_020eaa2c(buf, self->unk_5C) != 0) {
            func_ov049_02262a94(self, 3);
        }
    }

    func_0201aff4(self->unk_350, r4);
    if (func_02019e00(self->unk_564) == 3) {
        if (func_02019de8(self->unk_564) != 0) {
            func_ov049_02262a94(self, 1);
        }
    }
    return 1;
}
