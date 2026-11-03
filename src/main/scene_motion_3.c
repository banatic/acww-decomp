/* scene_motion_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201744c @ 0x0201744c, 0x94 bytes, Thumb
 * func_020173d8 @ 0x020173d8, 0x74 bytes, Thumb
 */

#include "types.h"

struct In {
    u8 pad_00[0x8e];
    s16 unk_8E;
    u8 pad_90[0x334 - 0x90];
    u8 unk_334;
    u8 pad_335[0x478 - 0x335];
    u32 unk_478;
    u32 unk_47C;
    u32 unk_480;
    u8 pad_484[0x514 - 0x484];
    u8 unk_514;
};

struct UnkStruct_0201744c {
    u8 pad_00[0xac];
    u32 unk_AC;
};

extern u16 data_020c80f8;
extern int func_02057d0c(int a0, void *a1);
extern void func_02016764(void *a0, void *a1, int a2, unsigned int a3, int a4, int a5, int a6, int a7);
extern int func_020912d4(int a0, u32 *a1, s16 *a2, int a3);
extern int func_0200442c(void *a0, int a1, int a2, int a3);
extern void func_02019af0(void *a0, int a1);
extern int func_020164cc(void *, int);
extern void func_0209129c(int);
extern void func_02091278(int, void *, void *, int);

int func_0201744c(struct UnkStruct_0201744c *out, struct In *self)
{
    s16 s;
    u32 v[3];

    v[0] = self->unk_478;
    v[1] = self->unk_47C;
    v[2] = self->unk_480;
    s = self->unk_8E;

    func_02057d0c(0xb, self);
    func_02016764(&self->unk_334, self, 0x29, data_020c80f8, 1, 0x1000, 0, 0);
    out->unk_AC = func_020912d4(0x40, v, &s, 0);
    func_0200442c(&self->unk_514, 0x6f, 0x7f, 0);
    func_02019af0(out, 0);
    return 1;
}

void func_020173d8(void *a, void *b)
{
    int field;

    if (func_020164cc((char *) b + 0x334, (int) b) != 0) {
        func_02016764((char *) b + 0x334, b, 0x2a, 0, 1, 0x1000, 0, 0);
        field = *(int *) ((char *) a + 0xac);
        if (field != -1) {
            func_0209129c(field);
        }
        ((char *) a)[0x98] = 1;
    } else {
        field = *(int *) ((char *) a + 0xac);
        if (field != -1) {
            func_02091278(field, (char *) b + 0x478, (char *) b + 0x8e, 0);
        }
    }
}
