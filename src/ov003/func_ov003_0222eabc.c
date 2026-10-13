/* func_ov003_0222eabc @ 0x0222eabc, 0xd8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0222eabc;

typedef struct {
    void (*fn)(struct UnkStruct_0222eabc *e);
    int pad_04;
} Handler;

struct UnkStruct_0222eabc {
    u8 pad_00[0x22c];
    int unk_22C;
    u8 pad_230[8];
    u16 unk_238;
    u16 unk_23A;
    u16 unk_23C;
    u8 pad_23E[0x24d - 0x23e];
    s8 unk_24D;
    u8 pad_24E[2];
    u8 unk_250;
    u8 unk_251;
    u8 pad_252[0xa];
};

extern struct UnkStruct_0222eabc data_ov003_02260e4c[];
extern Handler data_ov003_0223c2ac[];

extern void func_ov003_0222e358(struct UnkStruct_0222eabc *e, int n);
extern void func_ov003_02234030(struct UnkStruct_0222eabc *e, int n);
extern void func_0209129c(int h);
extern void func_ov003_0222e6c4(int idx, int n);

void func_ov003_0222eabc(int idx, int a)
{
    struct UnkStruct_0222eabc *e = &data_ov003_02260e4c[idx];
    int v;

    e->unk_251 = 0xb;
    e->unk_238 = 0;
    e->unk_23C = 0;
    func_ov003_0222e358(e, 0x64);
    e->unk_23A = (u16) a;

    v = e->unk_24D;
    if (v >= 0 && v < 0x3c) {
        data_ov003_0223c2ac[v].fn(e);

        switch (e->unk_24D) {
            case 0xc:
            case 0xd:
            case 0x1b:
            case 0x1c:
            case 0x1d:
                func_ov003_02234030(e, 1);
                break;
            case 0x39:
                if (e->unk_22C != -1) {
                    func_0209129c(e->unk_22C);
                    e->unk_22C = -1;
                }
                break;
        }
    } else {
        func_ov003_0222e6c4(idx, 0);
        e->unk_250 = 4;
    }
}
