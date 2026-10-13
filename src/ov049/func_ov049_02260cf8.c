/* func_ov049_02260cf8 @ 0x02260cf8, 0xb4 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02260cf8 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xbc - 0x44];
    int unk_BC;
    int unk_C0;
} UnkStruct_02260cf8;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 h;
} Msg;

extern u8 data_021f43ec;
extern int func_0206fc6c(void);
extern u16 *func_0206faf0(void);
extern int func_0204c878(u16 *p);
extern void func_02015fb0(UnkStruct_02260cf8 *self, int a, int b, int c, int d, int e);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov049_02263298;

void func_ov049_02260cf8(UnkStruct_02260cf8 *self)
{
    Msg m;
    int h;
    u16 *p;
    int i;

    self->unk_BC = 0;
    self->unk_C0 = 0;
    h = self->unk_40;
    m.b = data_021f43ec;
    if (func_0206fc6c() != 0) {
        p = func_0206faf0();
        m.h = 0xfff1;
        for (i = 0; i < 15; i++) {
            if (p[i] == 0xfff1) {
                break;
            }
            m.h = p[i];
            self->unk_BC = self->unk_BC + func_0204c878(&m.h) / 4;
        }
        if (self->unk_BC == 0) {
            m.b = 0x17;
        } else {
            func_02015fb0(self, self->unk_BC, 1, 0xa, 0, 0);
            m.b = 0x1b;
        }
    } else {
        m.b = 0x15;
    }
    func_0206844c(h, &m.b, data_ov049_02263298);
}
