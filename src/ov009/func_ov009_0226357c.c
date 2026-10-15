/* func_ov009_0226357c @ 0x0226357c, 0xcc bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec3 {
    int x, y, z;
};

struct UnkStruct_0226357c {
    u8 pad_00[0x22c];
    u32 unk_22C;
    u32 unk_230;
    u8 pad_234[0x236 - 0x234];
    u8 unk_236;
    u8 pad_237[0x282 - 0x237];
    u16 counter282;
};

extern int func_ov009_02264c90(struct UnkStruct_0226357c *self);
extern int func_ov009_022631b4(struct UnkStruct_0226357c *self);
extern int func_ov009_0226321c(struct UnkStruct_0226357c *self, struct Vec3 *v, s16 *local);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern int func_020310c8(int a);
extern int func_020b65c4(void);
extern int func_020b5ea0(int a, int b, struct Vec3 *v, int c, int d, u32 e, u32 f);
extern void func_020b22ac(int a);

void func_ov009_0226357c(struct UnkStruct_0226357c *self)
{
    s16 local;
    struct Vec3 v;
    unsigned int threshold;
    int v1;
    int v2;
    int v3;
    int v6;
    int v7;

    self->counter282++;
    func_ov009_02264c90(self);
    threshold = 0x14;
    if (func_ov009_02264c90(self) == 1) {
        threshold += 0xc;
    }
    if (self->counter282 < threshold) {
        return;
    }

    v1 = func_ov009_022631b4(self);
    v2 = func_ov009_0226321c(self, &v, &local);
    if (v2 == 0) {
        return;
    }
    v3 = func_020b5e10();
    if (func_020b6098(v3, v1) == 0) {
        return;
    }

    v.y = func_020310c8(0);
    v.z += 0x1000;
    v6 = func_020b5e10();
    v7 = func_020b65c4();
    func_020b5ea0(v6, v7, &v, 0x0f000000, (s16) (local + 0x8000), self->unk_22C, self->unk_230);

    func_020b22ac(func_ov009_02264c90(self));
    self->unk_236 = (self->unk_236 & ~1) | 1;
}
