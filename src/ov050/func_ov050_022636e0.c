/* func_ov050_022636e0 @ 0x022636e0, 0xe0 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022636e0 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_022636e0;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

extern int func_0206fc6c(void);
extern int func_020984e8(void);
extern int func_0202e9fc(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern void func_0209a050(int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_02015330(UnkStruct_022636e0 *self, u16 *p, int a, int b, int c);
extern int func_02099640(int t);
extern int func_0209a850(int a);
extern int func_0209b0f0(int a);
extern void func_0209bb90(int a, int b);
extern int func_ov050_02260510(int a);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov050_02265824;
extern int data_ov050_02265804;

void func_ov050_022636e0(UnkStruct_022636e0 *self)
{
    Msg m;
    int h;
    int t;
    int r;
    unsigned int ok;

    h = self->unk_40;
    m.b = 4;
    if (func_0206fc6c() != 0) {
        t = func_020984e8();
        if (func_0202e9fc() != 0) {
            r = func_0206fc8c();
            m.unk_02 = (u16) func_0209a034(r);
            if (r >= 0) {
                func_0209a050(r);
            }
            if (func_0204bcdc(&m.unk_02) != 0) {
                m.unk_04 = 0xfff1;
                r = func_0204bc64(&m.unk_02);
                ok = (r == func_0204bc64(&m.unk_04)) ? 1 : 0;
            } else {
                ok = (m.unk_02 == 0xfff1) ? 1 : 0;
            }
            if (ok == 0) {
                func_02015330(self, &m.unk_02, 2, 5, 0);
            }
            m.b = 3;
            func_0209bb90(func_0209b0f0(func_0209a850(func_02099640(t))), 1);
        }
    }
    if (func_ov050_02260510(self->unk_B4) != 0) {
        func_0206844c(h, &m.b, (int) &data_ov050_02265824);
    } else {
        func_0206844c(h, &m.b, (int) &data_ov050_02265804);
    }
}
