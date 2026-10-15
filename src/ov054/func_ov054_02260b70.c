/* func_ov054_02260b70 @ 0x02260b70, 0x90 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260b70 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
} UnkStruct_02260b70;

typedef struct Elem {
    int w[3];
} Elem;

extern Elem data_ov054_02262fac[];
extern u8 data_ov054_02262984[];

extern int func_020160b4(UnkStruct_02260b70 *self);
extern int func_020ab504(int a);
extern int func_0202ea40(char *p, u8 *q, int a);
extern void func_0202ea28(char *p, u8 *q);
extern void func_0206844c(int h, u8 *p, int k);

void func_ov054_02260b70(UnkStruct_02260b70 *self, unsigned int callbackArgument1)
{
    u8 m[2];
    int h;
    int a;
    int code;
    int idx;
    int v;

    h = self->unk_40;
    a = func_020ab504(func_020160b4(self));
    code = 0xff;
    idx = 1;
    v = (int) self->unk_1E;
    if (v >= 0 && v <= 0x19) {
        if (a == 1) {
            code = data_ov054_02262984[*(int *) (self->unk_B0 + 0x80c)];
            idx = 0;
        } else if (func_0202ea40(self->unk_B0, m, 0) != 0) {
            func_0202ea28(self->unk_B0, m);
        }
    }
    if (code != 0xff) {
        int k;
        k = data_ov054_02262fac[*(int *) (self->unk_B0 + 0x808)].w[idx];
        m[1] = (u8) code;
        func_0206844c(h, &m[1], k);
    }
}
