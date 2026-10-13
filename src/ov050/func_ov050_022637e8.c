/* func_ov050_022637e8 @ 0x022637e8, 0xec bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022637e8 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    char *unk_B4;
    char pad_B8[0xc4 - 0xb8];
    int unk_C4;
} UnkStruct_022637e8;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
} Msg;

extern int func_0206fc6c(void);
extern int func_0206f680(void);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0204c7f0(u16 *p);
extern void func_02015fb0(UnkStruct_022637e8 *self, int a, int b, int c, int d, int e);
extern void func_02015de4(UnkStruct_022637e8 *self, u16 *p, int a, int b);
extern int func_ov050_02260510(char *p);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov050_02265824;
extern int data_ov050_02265804;

void func_ov050_022637e8(UnkStruct_022637e8 *self)
{
    Msg m;
    int h;
    u16 *p;
    int r;
    unsigned int ok;

    h = self->unk_40;
    m.b = 0x1b;
    if (func_0206fc6c() == 1) {
        *(u16 *) (self->unk_B4 + 0x732) = (u16) func_0206f680();
        p = (u16 *) (self->unk_B4 + 0x732);
        if (func_0204bcdc(p) != 0) {
            m.unk_02 = 0xfff1;
            r = func_0204bc64(p);
            ok = (r == func_0204bc64(&m.unk_02)) ? 1 : 0;
        } else {
            ok = (*p == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            self->unk_C4 = func_0204c7f0((u16 *) (self->unk_B4 + 0x732));
            if (self->unk_C4 != 0) {
                func_02015fb0(self, self->unk_C4, 0, 0xa, 0, 0);
                func_02015de4(self, (u16 *) (self->unk_B4 + 0x732), 1, 7);
                m.b = 0x1a;
            }
        }
    }
    if (func_ov050_02260510(self->unk_B4) != 0) {
        func_0206844c(h, &m.b, (int) &data_ov050_02265824);
    } else {
        func_0206844c(h, &m.b, (int) &data_ov050_02265804);
    }
}
