/* func_ov047_02261a24 @ 0x02261a24, 0xc4 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261a24 {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261a24;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

extern int func_020984e8(void);
extern int func_0206fc6c(void);
extern int func_0202e9fc(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern void func_0209a050(int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_02015330(UnkStruct_02261a24 *self, u16 *p, int a, int b, int c);
extern int func_02099640(int t);
extern int func_0209a850(int a);
extern int func_0209b0f0(int a);
extern void func_0209bb90(int a, int b);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov047_02262fc0;

void func_ov047_02261a24(UnkStruct_02261a24 *self)
{
    Msg m;
    int h;
    int t;
    int r;
    unsigned int ok;

    h = self->unk_40;
    m.b = 0xe8;
    t = func_020984e8();
    if (func_0206fc6c() != 0 && func_0202e9fc() != 0) {
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
        func_0209bb90(func_0209b0f0(func_0209a850(func_02099640(t))), 1);
        m.b = 0xe7;
    }
    func_0206844c(h, &m.b, (int) &data_ov047_02262fc0);
}
