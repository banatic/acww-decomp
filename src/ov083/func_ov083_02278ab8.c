/* func_ov083_02278ab8 @ 0x02278ab8, 0xac bytes, Thumb, module ov083
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
    u8 unk_00;
    u8 unk_01;
    u16 h;
} Msg;

extern int func_020160b4(UnkStruct_02278ab8 *self);
extern int func_020ab504(int a);
extern int func_0209a050(int a);
extern void func_02015330(UnkStruct_02278ab8 *self, u16 *p, int a, int b, int c);
extern int func_020644cc(int a);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov083_02279338;
extern int data_ov083_02279348;

void func_ov083_02278ab8(UnkStruct_02278ab8 *self)
{
    Msg m;
    int a;
    int k;
    int code;
    int v;

    a = func_020ab504(func_020160b4(self));
    k = (int) &data_ov083_02279338;
    code = 0xff;
    v = self->unk_B4;
    if (v >= 0) {
        k = (int) &data_ov083_02279348;
        if (self->unk_1E == 0 && a == 0) {
            if (v >= 0) {
                func_0209a050(v);
                m.h = 0x37e0;
                func_02015330(self, &m.h, 0, 5, 0);
            }
            code = 2;
        }
        if (code != 0xff) {
            m.unk_00 = (u8) code;
            func_0206844c(self->unk_40, &m.unk_00, k);
        }
    } else {
        if (self->unk_1E == 0xa && a == 0) {
            if (func_020644cc(3) == 0) {
                code = 0xc;
            } else {
                code = (u8) (func_020644cc(0xb) + 0x1c);
            }
        }
        if (code != 0xff) {
            m.unk_01 = (u8) code;
            func_0206844c(self->unk_40, &m.unk_01, k);
        }
    }
}
