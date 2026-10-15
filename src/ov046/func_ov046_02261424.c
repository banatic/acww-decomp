/* func_ov046_02261424 @ 0x02261424, 0xc4 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261424_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xc0 - 0x44];
    int unk_C0;
    u8 unk_C4;
    u8 unk_C5;
} UnkStruct_02261424_2;

typedef struct UnkStruct_02261424 {
    u8 b[16];
} UnkStruct_02261424;

extern int func_0206fc6c(void);
extern void func_020b12e0(int *out, int a);
extern void func_02015ed0(UnkStruct_02261424_2 *self, int a, int b);
extern void func_02015ea0(UnkStruct_02261424_2 *self, int a, int b);
extern void func_02015fb0(UnkStruct_02261424_2 *self, int a, int b, int c, int d, int e);
extern int func_020683e4(int h, int a, u8 *p, int k);
extern void func_020b14c0(int a);
extern int func_020b1558(void);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov046_02262420;
extern int data_ov046_02261fe8;

void func_ov046_02261424(UnkStruct_02261424_2 *self)
{
    UnkStruct_02261424 m;
    int h;
    int code;
    int v;

    h = self->unk_40;
    m.b[0] = 0xc;
    if (func_0206fc6c() != 0) {
        *(int *) &m.b[4] = 0;
        *(int *) &m.b[8] = 0;
        func_020b12e0((int *) &m.b[4], self->unk_C0);
        func_02015ed0(self, m.b[8], 2);
        func_02015ea0(self, m.b[7], 3);
        func_02015fb0(self, m.b[5], 5, 2, 0, 0);
        code = 0x19;
        v = (int) m.b[6];
        if (v > 0xc) {
            code = 0x1a;
            v -= 0xc;
        }
        func_02015fb0(self, v, 4, 2, 0, 0);
        m.b[1] = (u8) code;
        func_020683e4(h, 8, &m.b[1], (int) &data_ov046_02262420);
        m.b[0] = 8;
    } else {
        self->unk_C5 = (u8) (0x10 - ((void) (func_020b14c0(self->unk_C0)), func_020b1558()));
        self->unk_C4 = 0;
    }
    func_0206844c(h, &m.b[0], (int) &data_ov046_02261fe8);
}
