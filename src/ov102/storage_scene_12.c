/* storage_scene_12: 3 functions, module ov102
 * mwccarm 1.2/base -O4,s
 * func_ov102_0229d54c @ 0x0229d54c, 0x9c bytes, Thumb
 * func_ov102_0229d508 @ 0x0229d508, 0x44 bytes, Thumb
 * func_ov102_0229d4cc @ 0x0229d4cc, 0x3c bytes, Thumb
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x225c];
    u8 unk_225C[0x284];
    u32 unk_24E0;
    u32 unk_24E4;
    u8 pad_24E8[0xba];
    u8 unk_25A2;
} UnkStruct_0229d54c;

typedef struct {
    char pad_00[0x24e0];
    int unk_24E0;
    int unk_24E4;
} UnkStruct_0229d4cc;

extern void func_ov002_02209d68(void *, u32, u32);
extern int func_ov002_02209d38(void *, u32, u32, u32);
extern int func_ov002_02209d8c(void *);
extern int func_ov102_0229d178(UnkStruct_0229d54c *, int);
extern int func_ov102_0229d444(UnkStruct_0229d54c *, int);
extern int func_ov102_0229d1e8(UnkStruct_0229d54c *, int);
extern void func_ov102_0229cd08(UnkStruct_0229d54c *);
extern void func_ov102_0229c298(UnkStruct_0229d54c *, u32);
extern void func_ov102_0229c288(UnkStruct_0229d54c *, u32);
extern unsigned char *func_ov002_02208098(UnkStruct_0229d54c *, unsigned char value);
extern int func_ov102_0229d454(int arg0, unsigned int arg1);
extern int func_ov102_0229d464(int arg0, unsigned int arg1);
extern int func_ov102_0229d4ac(void *receiver);
extern int func_ov102_0229d47c(int);
extern void func_ov102_0229cc90(UnkStruct_0229d4cc *, int);

void func_ov102_0229d54c(UnkStruct_0229d54c *self, int a1, int a2)
{
    int v;
    int ret;

    self->unk_25A2 = a1;
    func_ov002_02209d68(&self->unk_225C, self->unk_24E0, self->unk_24E4);
    v = func_ov102_0229d178(self, a1);
    if (func_ov102_0229d444(self, a1) != 0) {
        v -= 8;
    }
    ret = func_ov102_0229d1e8(self, a1);
    func_ov002_02209d38(&self->unk_225C, ret, v, a2);
    func_ov002_02209d8c(&self->unk_225C);
    func_ov102_0229cd08(self);
    if (func_ov102_0229d444(self, a1) != 0) {
        func_ov102_0229c298(self, 0x200);
    } else {
        func_ov102_0229c288(self, 0x200);
    }
    func_ov002_02208098(self, 13);
}

void func_ov102_0229d508(int p1, int p2, int p3)
{
    int x = 0x25;
    if (p3 >= 108) {
        if (func_ov102_0229d454(p1, p2)) {
            x = func_ov102_0229d4ac((void *) p1);
        }
    } else {
        if (func_ov102_0229d464(p1, p2)) {
            x = func_ov102_0229d47c(p1);
        }
    }
    if (x != 0x25) {
        p2 = x;
    }
    func_ov102_0229d54c((UnkStruct_0229d54c *) p1, p2, 4);
}

void func_ov102_0229d4cc(UnkStruct_0229d4cc *a, int b, int c)
{
    func_ov102_0229cc90(a, b);
    a->unk_24E0 = func_ov102_0229d1e8((UnkStruct_0229d54c *) a, b);
    a->unk_24E4 = func_ov102_0229d178((UnkStruct_0229d54c *) a, b);
    func_ov102_0229d54c((UnkStruct_0229d54c *) a, c, 4);
}
