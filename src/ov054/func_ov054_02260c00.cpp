/* func_ov054_02260c00 @ 0x02260c00, 0x19c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov054_0226300419func_ov054_02260c00Ej
 */

#include "cpp/ov054/Obj_ov054_02263004.h"

#include "types.h"

extern "C" int func_020160b4(void *);
extern "C" int func_020ab504(int);
extern "C" int func_020984e8(void);
extern "C" void func_020157d4(void *, void (*)(void), int, int);
extern "C" void func_02015828(void *, int);
extern "C" void func_ov054_02261cc4(void *, int);
extern "C" void func_ov054_02261850(void);
extern "C" void func_ov054_02261f44(void *);
extern "C" void func_0206f910(void);
extern "C" void func_0206f92c(void);
extern "C" int func_02099020(int, int);
extern "C" void func_02098ff8(int, int);
extern "C" void func_0206844c(int, u8 *, void *);

extern "C" u8 data_ov054_02262978[];
typedef struct {
    void *a;
    int b;
    int c;
} E12;
extern "C" E12 data_ov054_02262fac[];

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    int unk_40;
    char pad_44[0x6c];
    int unk_B0;
} UnkStruct_02260c00;

void Obj_ov054_02263004::func_ov054_02260c00(unsigned int a1)
{
    UnkStruct_02260c00 *p = (UnkStruct_02260c00 *) this;
    u8 m;
    int h;
    int r;
    int q;
    int code;
    int v;

    h = p->unk_40;
    r = func_020ab504(func_020160b4(p));
    q = func_020984e8();
    code = 0xff;
    v = p->unk_1E;
    switch (v) {
        case 0x5f:
            if (r == 0) {
                func_020157d4(p, func_ov054_02261850, 0xd, 0);
                func_02015828(p, 0);
                func_ov054_02261cc4(p, 0xb);
            } else if (r == 1) {
                code = data_ov054_02262978[*(int *) (p->unk_B0 + 0x80c)];
            }
            break;
        case 0:
        case 0x52:
        case 0x53:
        case 0x56:
            ((Obj_ov054_02263004 *) p)->func_ov054_022608ac(a1);
            break;
        case 3:
        case 9:
            if (r == 0) {
                func_02015828(p, 1);
                func_ov054_02261cc4(p, 1);
            }
            break;
        case 0x10:
            switch (r) {
                case 0:
                    code = 0x11;
                    break;
                case 1:
                    code = 0xe;
                    func_0206f910();
                    break;
            }
            break;
        case 0xc:
            if (r == 0) {
                func_0206f92c();
                code = 7;
            }
            break;
        case 4:
        case 0x1c:
        case 0x34:
        case 0x5d:
        case 0x5e:
            switch (r) {
                case 2:
                    if (func_02099020(q, 4) == 0) {
                        code = 0x1a;
                        func_02098ff8(q, 4);
                    } else {
                        code = 0x19;
                    }
                    break;
                case 3:
                    if (func_02099020(q, 1) != 0) {
                        code = 0x60;
                    } else {
                        code = 0x35;
                    }
                    break;
            }
            break;
        case 0x38:
        case 0x39:
            if (r == 1) {
                func_ov054_02261f44(p);
                code = 0x3a;
            }
            break;
    }

    if (code != 0xff) {
        void *t = data_ov054_02262fac[*(int *) (p->unk_B0 + 0x808)].a;
        m = (u8) code;
        func_0206844c(h, &m, t);
    }
}
