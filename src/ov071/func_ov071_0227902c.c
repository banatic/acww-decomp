/* func_ov071_0227902c @ 0x0227902c, 0xc4 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0227902c {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_0227902c;

typedef struct Msg {
    u8 b;
    u8 pad_01;
    u16 unk_02;
    u16 unk_04;
} Msg;

extern int func_0206fc6c(void);
extern int func_0206fc8c(void);
extern int func_0209a034(int a);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_020984e8(void);
extern int func_02099670(int a);
extern void func_02088a60(int a);
extern int func_02015330(UnkStruct_0227902c *self, u16 *p, int a, int b, int c);
extern void func_0209a050(int a);
extern void func_ov071_02279118(UnkStruct_0227902c *self, int a);
extern int func_020155cc(UnkStruct_0227902c *self);
extern void func_0206844c(int h, u8 *p, int k);
extern int data_ov071_0227a180;

void func_ov071_0227902c(UnkStruct_0227902c *self)
{
    Msg m;
    int h;
    int t;
    int r;
    int v;
    unsigned int ok;

    h = self->unk_40;
    m.b = 0x24;
    if (func_0206fc6c() != 0) {
        t = func_0206fc8c();
        m.unk_02 = (u16) func_0209a034(t);
        if (func_0204bcdc(&m.unk_02) != 0) {
            m.unk_04 = 0xfff1;
            r = func_0204bc64(&m.unk_02);
            ok = (r == func_0204bc64(&m.unk_04)) ? 1 : 0;
        } else {
            ok = (m.unk_02 == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            v = func_02099670(func_020984e8());
            m.b = 0x25;
            func_02088a60(v);
            func_02015330(self, &m.unk_02, 0, 4, 0);
            if (t >= 0) {
                func_0209a050(t);
            }
            func_ov071_02279118(self, 1);
        } else {
            func_020155cc(self);
        }
    } else {
        func_020155cc(self);
    }
    func_0206844c(h, &m.b, (int) &data_ov071_0227a180);
}
