/* func_0201a0dc @ 0x0201a0dc, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0201a0dc {
    u8 pad_00[0x14];
    u8 unk_14[8];
    u32 unk_1C;
    u8 pad_20[0x24 - 0x20];
    u32 unk_24;
    u8 pad_28[0x74 - 0x28];
    u32 unk_74;
    u32 unk_78;
    u32 unk_7C;
} UnkStruct_0201a0dc;

extern int func_0201a3e8(void *self);
extern void *func_02082da8(void *p);
extern void func_0205d7b8(void *p, int a, int b, int c);
extern int func_0205d8a0(void *p);
extern unsigned char *NNS_G3dGetAnmByIdx(int a, int b);
extern void func_0205678c(void *dst, int src, int a, int b, int c, int d);
extern void func_02056730(void *p);
extern int func_0201a2e8(void *self, int field);
extern void func_0201a1d4(void *self, int a, int b);

void func_0201a0dc(UnkStruct_0201a0dc *self, int a, int b, int c, int d)
{
    void *r7;

    if (func_0201a3e8(self) == 0) {
        return;
    }

    r7 = func_02082da8(self->unk_14);

    if (a != 0 || self->unk_74 != a) {
        func_0205d7b8(r7, a, 1, 0);
        NNS_G3dGetAnmByIdx(func_0205d8a0(r7), 0);
        func_0205678c(&self->unk_1C, func_0205d8a0(r7), 0, 0, c, 0x1000);
        self->unk_74 = a;
        self->unk_24 = 0;
        func_02056730(&self->unk_1C);
    }

    if (d == 2 || func_0201a2e8(self, self->unk_78) == 0) {
        func_0201a1d4(self, b, 0);
    } else {
        self->unk_7C = b;
    }
}
