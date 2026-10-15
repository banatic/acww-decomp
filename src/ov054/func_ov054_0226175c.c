/* func_ov054_0226175c @ 0x0226175c, 0xf4 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0226175c {
    char pad_00[0x808];
    int unk_808;
} UnkStruct_0226175c;

typedef struct UnkStruct_0226175c_2 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_0226175c *unk_B0;
} UnkStruct_0226175c_2;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

typedef struct UnkStruct_0226175c_3 {
    int a;
    int b;
    int c;
} UnkStruct_0226175c_3;

extern UnkStruct_0226175c_3 data_ov054_02262fac[];
extern int func_0206fc6c(void);
extern int func_020984e8(void);
extern int func_02099640(int a);
extern int func_0209a850(int a);
extern int func_0202e9fc(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern void func_0209a050(int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_02015330(UnkStruct_0226175c_2 *self, u16 *p, int a, int b, int c);
extern int func_0209af80(int v, char *q);
extern void *func_0209b0f0(void *record);
extern void func_0209bb90(void *a, int b);
extern void func_ov054_02261cc4(UnkStruct_0226175c_2 *self, int a);
extern void func_0206844c(int h, u8 *p, int k);

void func_ov054_0226175c(UnkStruct_0226175c_2 *self)
{
    Msg m;
    int h;
    int v;
    int k;
    int t;
    int r;
    u8 code;
    unsigned int ok;

    h = self->unk_40;
    k = data_ov054_02262fac[self->unk_B0->unk_808].a;
    code = 0x51;
    if (func_0206fc6c() != 0) {
        v = func_0209a850(func_02099640(func_020984e8()));
        if (func_0202e9fc() != 0) {
            t = func_0206fc8c();
            m.unk_02 = (u16) func_0209a034(t);
            if (t >= 0) {
                func_0209a050(t);
            }
            if (func_0204bcdc(&m.unk_02) != 0) {
                m.unk_04 = 0xfff1;
                r = func_0204bc64(&m.unk_02);
                ok = (r == func_0204bc64(&m.unk_04)) ? 1 : 0;
            } else {
                ok = (m.unk_02 == 0xfff1) ? 1 : 0;
            }
            if (ok == 0) {
                func_02015330(self, &m.unk_02, 2, 5, 1);
                if (func_0209af80(v, (char *) self->unk_B0 + 0xea) == 0) {
                    code = 0x57;
                } else {
                    code = 0x50;
                }
                func_0209bb90(func_0209b0f0((void *) v), 1);
            }
        }
    }
    func_ov054_02261cc4(self, 0);
    m.b = code;
    func_0206844c(h, &m.b, k);
}
