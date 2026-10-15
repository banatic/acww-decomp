/* func_ov054_02261c00 @ 0x02261c00, 0xc4 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261c00 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    char *unk_B0;
    char pad_B4[0xbc - 0xb4];
    u8 unk_BC;
} UnkStruct_02261c00;

typedef struct Elem {
    int w[3];
} Elem;
typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
} Msg;

extern Elem data_ov054_02262fac[];
extern int func_0206fc6c(void);
extern int func_0206f8e0(void);
extern int func_ov054_02261ddc(UnkStruct_02261c00 *self);
extern int func_02097864(int a);
extern int func_02015330(UnkStruct_02261c00 *self, u16 *p, int a, int b, int c);
extern void func_ov054_02261cc4(UnkStruct_02261c00 *self, int a);
extern int func_020155cc(UnkStruct_02261c00 *self);
extern void func_0206844c(int h, u8 *p, int k);

void func_ov054_02261c00(UnkStruct_02261c00 *self)
{
    Msg m;
    int h;
    int k;
    int code;

    h = self->unk_40;
    k = data_ov054_02262fac[*(int *) (self->unk_B0 + 0x808)].w[0];
    code = 0;
    self->unk_BC = 0;
    if (func_0206fc6c() != 0) {
        switch (func_0206f8e0()) {
            case 0:
                code = func_ov054_02261ddc(self);
                if (code == 9) {
                    code = 7;
                }
                break;
            case 1:
                if (func_02097864(0) != 0) {
                    code = 0xf;
                } else {
                    code = 0xb;
                }
                break;
            case 2:
                code = 0x5c;
                break;
            case 3:
                code = 0x62;
                break;
        }
        m.unk_02 = 0x1565;
        func_02015330(self, &m.unk_02, 0, 5, 1);
        func_ov054_02261cc4(self, 0xa);
    } else {
        code = 3;
        func_020155cc(self);
        func_ov054_02261cc4(self, 0);
    }
    m.b = (u8) code;
    func_0206844c(h, &m.b, k);
}
