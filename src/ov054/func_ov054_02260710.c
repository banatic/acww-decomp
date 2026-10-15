/* func_ov054_02260710 @ 0x02260710, 0xa8 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260710 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
    char pad_B4[0xc4 - 0xb4];
    int unk_C4;
} UnkStruct_02260710;

typedef struct Elem {
    int w[3];
} Elem;

extern Elem data_ov054_02262fac[];
extern int data_ov054_02262a18[];

extern int func_020984e8(void);
extern int func_020992fc(int a);
extern int func_020983e0(void);
extern int func_020983c4(int a);
extern void func_020983c0(int a, int b);
extern void func_02098ff8(int a, int b);
extern void func_0206844c(int h, u8 *p, int k);

void func_ov054_02260710(UnkStruct_02260710 *self)
{
    int h;
    int a;
    int b;
    int k;
    u8 buf;
    int v;
    int i;
    int lo;
    int code;

    h = self->unk_40;
    k = data_ov054_02262fac[*(int *) (self->unk_B0 + 0x808)].w[0];
    a = func_020984e8();
    b = func_020992fc(a);
    v = func_020983e0();
    code = (u8) (func_020983c4(b) + 0x1f);
    for (i = 1; i < 0x15; i++) {
        lo = data_ov054_02262a18[i];
        if (v >= lo && v < data_ov054_02262a18[i + 1]) {
            func_020983c0(b, (u8) i);
            if (self->unk_C4 < lo) {
                func_02098ff8(a, 0x16);
                code = (u8) (i + 0x1f);
            } else {
                code = (u8) (i + 0x1f);
            }
        }
    }
    buf = (u8) code;
    func_0206844c(h, &buf, k);
}
