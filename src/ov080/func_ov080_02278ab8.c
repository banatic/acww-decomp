/* func_ov080_02278ab8 @ 0x02278ab8, 0x78 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02278ab8 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278ab8;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 h;
} Msg;

extern int func_020160b4(UnkStruct_02278ab8 *self);
extern int func_020ab504(int a);
extern int func_020984e8(void);
extern void func_0209a050(int a);
extern int func_02015330(UnkStruct_02278ab8 *self, u16 *p, int a, int b, int c);
extern int func_02099020(int a, int b);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov080_02279398;

void func_ov080_02278ab8(UnkStruct_02278ab8 *self)
{
    Msg m;
    int t;
    int a;
    int k;
    int v;
    int code;

    a = func_020ab504(func_020160b4(self));
    t = func_020984e8();
    code = 0xff;
    v = self->unk_B4;
    if (v >= 0) {
        k = (int) &data_ov080_02279398;
        if (self->unk_1E == 0 && a == 0) {
            if (v >= 0) {
                func_0209a050(v);
                m.h = 0x37e0;
                func_02015330(self, &m.h, 0, 5, 0);
            }
            code = 2;
        }
        if (code != 0xff) {
            m.b = (u8) code;
            func_0206844c(self->unk_40, &m.b, k);
        }
    } else {
        func_02099020(t, 1);
    }
}
