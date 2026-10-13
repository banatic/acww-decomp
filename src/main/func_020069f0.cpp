/* func_020069f0 @ 0x020069f0, 0x974 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020d82b4.h"

typedef void (Obj_020d82b4::*PMF)(int);

typedef struct UnkStruct_020069f0 UnkStruct_020069f0;
struct UnkStruct_020069f0 {
    short unk_00;
    short unk_02;
    int unk_04;
};

extern "C" int func_02096518(int *, int, int);
extern "C" int func_0200f290(Obj_020d82b4 *, int);
extern "C" void func_0200f268(Obj_020d82b4 *, int);
extern "C" UnkStruct_020069f0 *func_020966c4(int);
extern "C" int func_0200ea0c(Obj_020d82b4 *, int);
extern "C" int func_020778c8(short *);
extern "C" void MI_CpuCopy8(void *, void *, unsigned int);

#define TABLE                                                                                                                 \
    static PMF tbl[147] = {                                                                                                   \
        &Obj_020d82b4::func_0200db84,       &Obj_020d82b4::func_0200d53c,       &Obj_020d82b4::func_0200d478,                 \
        &Obj_020d82b4::func_0200d144,       &Obj_020d82b4::func_0200cabc,       &Obj_020d82b4::func_0200c978,                 \
        &Obj_020d82b4::func_ov003_0221947c, &Obj_020d82b4::func_0200c7d0,       &Obj_020d82b4::func_ov004_0222bd40,           \
        &Obj_020d82b4::func_ov004_0222bb08, &Obj_020d82b4::func_ov004_0222b88c, &Obj_020d82b4::func_ov004_0222b5b4,           \
        &Obj_020d82b4::func_ov004_0222b468, &Obj_020d82b4::func_ov004_0222b2f0, &Obj_020d82b4::func_ov004_0222b0b8,           \
        &Obj_020d82b4::func_ov004_0222ae54, &Obj_020d82b4::func_0200c368,       &Obj_020d82b4::func_ov003_02218f80,           \
        &Obj_020d82b4::func_ov004_0222acc0, &Obj_020d82b4::func_0200c198,       &Obj_020d82b4::func_0200c01c,                 \
        &Obj_020d82b4::func_0200be98,       &Obj_020d82b4::func_ov003_02218dfc, &Obj_020d82b4::func_ov003_02218c24,           \
        &Obj_020d82b4::func_0200bbc8,       &Obj_020d82b4::func_0200b3b4,       &Obj_020d82b4::func_0200aad4,                 \
        &Obj_020d82b4::func_0200a5b8,       &Obj_020d82b4::func_ov004_0222aa8c, &Obj_020d82b4::func_ov004_0222a3cc,           \
        &Obj_020d82b4::func_ov004_0222a178, &Obj_020d82b4::func_ov004_02229e70, &Obj_020d82b4::func_ov004_02229cf8,           \
        &Obj_020d82b4::func_ov004_02229b88, &Obj_020d82b4::func_ov004_022299f8, &Obj_020d82b4::func_ov004_022298dc,           \
        &Obj_020d82b4::func_ov004_02229634, &Obj_020d82b4::func_ov004_02229384, &Obj_020d82b4::func_ov004_0222913c,           \
        &Obj_020d82b4::func_ov004_02228ef4, &Obj_020d82b4::func_ov004_02228db0, &Obj_020d82b4::func_ov004_02228ba0,           \
        &Obj_020d82b4::func_ov004_02228ad4, &Obj_020d82b4::func_ov004_022289b4, &Obj_020d82b4::func_ov004_022287b4,           \
        &Obj_020d82b4::func_ov004_0222852c, &Obj_020d82b4::func_ov004_02228318, &Obj_020d82b4::func_ov004_022281e0,           \
        &Obj_020d82b4::func_0200a3a8,       &Obj_020d82b4::func_0200a2e0,       &Obj_020d82b4::func_0200a220,                 \
        &Obj_020d82b4::func_02009f94,       &Obj_020d82b4::func_02009ed4,       &Obj_020d82b4::func_02009e24,                 \
        &Obj_020d82b4::func_ov004_022280ac, &Obj_020d82b4::func_ov004_02227f8c, &Obj_020d82b4::func_ov003_022187f0,           \
        &Obj_020d82b4::func_ov003_02218524, &Obj_020d82b4::func_ov003_022183cc, &Obj_020d82b4::func_ov003_022181c8,           \
        &Obj_020d82b4::func_ov003_02217d54, &Obj_020d82b4::func_ov003_02217a6c, &Obj_020d82b4::func_ov003_02217608,           \
        &Obj_020d82b4::func_02009c48,       &Obj_020d82b4::func_ov004_02227d7c, &Obj_020d82b4::func_ov004_0222794c,           \
        &Obj_020d82b4::func_ov004_02227758, &Obj_020d82b4::func_ov004_02227574, &Obj_020d82b4::func_ov004_0222743c,           \
        &Obj_020d82b4::func_ov003_02217400, &Obj_020d82b4::func_ov003_02217070, &Obj_020d82b4::func_ov003_02216e94,           \
        &Obj_020d82b4::func_ov003_02216ba4, &Obj_020d82b4::func_ov003_022169a4, &Obj_020d82b4::func_ov003_02216640,           \
        &Obj_020d82b4::func_ov003_02216358, &Obj_020d82b4::func_ov003_02216080, &Obj_020d82b4::func_ov003_02215e38,           \
        &Obj_020d82b4::func_ov003_02215cb0, &Obj_020d82b4::func_ov003_02215ac4, &Obj_020d82b4::func_ov003_0221570c,           \
        &Obj_020d82b4::func_ov003_02215544, &Obj_020d82b4::func_ov003_02215454, &Obj_020d82b4::func_ov003_022152ec,           \
        &Obj_020d82b4::func_ov003_02215164, &Obj_020d82b4::func_ov003_02214ba0, &Obj_020d82b4::func_ov003_022145f8,           \
        &Obj_020d82b4::func_ov003_02213944, &Obj_020d82b4::func_ov003_022130dc, &Obj_020d82b4::func_ov003_02212ac0,           \
        &Obj_020d82b4::func_ov003_02212768, &Obj_020d82b4::func_ov003_0221246c, &Obj_020d82b4::func_ov003_02212388,           \
        &Obj_020d82b4::func_ov003_022121b8, &Obj_020d82b4::func_ov003_02211cbc, &Obj_020d82b4::func_ov003_022115a4,           \
        &Obj_020d82b4::func_ov003_02210eb8, &Obj_020d82b4::func_ov003_02210b38, &Obj_020d82b4::func_ov003_0221094c,           \
        &Obj_020d82b4::func_ov003_02210634, &Obj_020d82b4::func_ov003_022102d0, &Obj_020d82b4::func_ov003_0221013c,           \
        &Obj_020d82b4::func_ov003_0220ffc0, &Obj_020d82b4::func_ov003_0220fd00, &Obj_020d82b4::func_ov003_0220f9f8,           \
        &Obj_020d82b4::func_ov003_0220f6d8, &Obj_020d82b4::func_ov003_0220f478, &Obj_020d82b4::func_ov003_0220f390,           \
        &Obj_020d82b4::func_ov003_0220f2ec, &Obj_020d82b4::func_ov003_0220f16c, &Obj_020d82b4::func_ov003_0220ef74,           \
        &Obj_020d82b4::func_02009914,       &Obj_020d82b4::func_02009568,       &Obj_020d82b4::func_ov003_0220ed24,           \
        &Obj_020d82b4::func_ov003_0220ea04, &Obj_020d82b4::func_ov003_0220e828, &Obj_020d82b4::func_ov003_0220e518,           \
        &Obj_020d82b4::func_ov003_0220e11c, &Obj_020d82b4::func_02009310,       &Obj_020d82b4::func_02008d2c,                 \
        &Obj_020d82b4::func_ov003_0220e004, &Obj_020d82b4::func_02008be8,       &Obj_020d82b4::func_ov004_022272f0,           \
        &Obj_020d82b4::func_ov004_022271dc, &Obj_020d82b4::func_ov004_02227114, &Obj_020d82b4::func_ov004_02226f40,           \
        &Obj_020d82b4::func_ov004_02226e50, &Obj_020d82b4::func_ov004_02226da8, &Obj_020d82b4::func_ov003_0220dd90,           \
        &Obj_020d82b4::func_ov003_0220db40, &Obj_020d82b4::func_ov003_0220d874, &Obj_020d82b4::func_02008a2c,                 \
        &Obj_020d82b4::func_020088fc,       &Obj_020d82b4::func_02008690,       &Obj_020d82b4::func_02008418,                 \
        &Obj_020d82b4::func_ov068_02271f7c, &Obj_020d82b4::func_ov068_02271e78, &Obj_020d82b4::func_ov003_0220d674,           \
        &Obj_020d82b4::func_ov004_02226cfc, &Obj_020d82b4::func_ov004_02226a80, &Obj_020d82b4::func_ov004_022266f0,           \
        &Obj_020d82b4::func_ov004_022264f4, &Obj_020d82b4::func_ov004_022262f0, &Obj_020d82b4::func_ov003_0220d410,           \
        &Obj_020d82b4::func_02008350,       &Obj_020d82b4::func_020082fc,       &Obj_020d82b4::func_020082ec,                 \
    };

extern "C" void func_020069f0(Obj_020d82b4 *self)
{
    int v;
    int a;
    int b;
    UnkStruct_020069f0 *p;

    if (func_02096518(&v, -1, self->unk_800) == 0) {
        self->unk_8F8 = 147;
        return;
    }
    if (v >= 147) {
        self->unk_8F8 = 147;
        return;
    }
    if (func_0200f290(self, 0x12)) {
        if (v != 0x1a) {
            return;
        }
        if (self->unk_7F0 != 0x19) {
            return;
        }
        func_0200f268(self, 0x12);
    }
    self->unk_8F8 = v;
    p = func_020966c4(self->unk_800);
    if (p) {
        MI_CpuCopy8(&p->unk_04, self->unk_8F0, 8);
    }
    a = func_0200ea0c(self, self->unk_7F0);
    b = func_0200ea0c(self, v);
    if (a == 1 && b == 1) {
        return;
    }
    if (b == 1) {
        v = 2;
    }
    a = -1;
    p = func_020966c4(self->unk_800);
    if (p) {
        a = func_020778c8(&p->unk_02);
    }
    if (self->unk_C84 >= 0 && self->unk_C88 == v && a == self->unk_C84) {
        return;
    }
    {
        TABLE(self->*tbl[v])(a);
    }
}
