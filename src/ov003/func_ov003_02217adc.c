/* func_ov003_02217adc @ 0x02217adc, 0x114 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020110c4(void *out, void *self);
extern int func_02011368(void *self);
extern void func_0209971c(int val, void *ptr);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0200f27c(void *self, int a);
extern void func_02056fcc(void *ptr, int a, int b, int c, int d);
extern void func_ov003_02217c3c(void *out, int a, u8 b, int c, int d, s16 e, int f);
extern void func_ov003_02217c14(void *out, u8 a, int b, int c, s16 d);
extern void func_0200f328(void *self, int a);

typedef struct {
    u8 pad_00[0x2d0];
    u32 unk_2D0;
    u32 unk_2D4;
    u8 pad_2D8[0x7d4 - 0x2d8];
    u8 unk_7D4[0x11c];
    u8 unk_8F0;
} UnkStruct_02217adc;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    s16 unk_0C;
    u8 unk_0E;
} ArgSub;

typedef struct {
    u8 pad_00[0xc];
    ArgSub sub;
} Arg;

void func_ov003_02217adc(UnkStruct_02217adc *self, Arg *arg)
{
    ArgSub *p = &arg->sub;
    void *p7d4 = (char *) self + 0x7d4;
    void *p8f0;
    int var_10;
    int ret;
    u16 buf[4];
    int f0;
    u8 f4;
    int f1;
    int f2;
    s16 f3;

    func_020110c4(buf, self);
    ret = func_02011368(self);

    buf[1] = 0xfff1;
    func_0209971c(ret, &buf[1]);

    func_020109a0(self, 0x6b, 3, 0);
    func_0209971c(ret, buf);

    if ((p->unk_0E & 3) == 2) {
        u32 r1;
        func_0200f27c(self, 0);
        var_10 = 0;
        r1 = (self->unk_2D4 << 4) >> 16;
        func_02056fcc(&self->unk_2D0, r1, 3, 0x1000, (u16) (r1 - 1));
    } else {
        var_10 = 0x1000;
    }

    f0 = p->unk_00;
    f4 = p->unk_0E;
    f1 = p->unk_04;
    f2 = p->unk_08;
    f3 = p->unk_0C;

    func_ov003_02217c3c(p7d4, f0, f4, f1, f2, f3, var_10);

    p8f0 = (char *) self + 0x8f0;

    switch (f0) {
        case 0x39:
            f4 = (u8) (f4 | 0x10);
            break;
        case 0x10:
            f4 = (u8) (f4 | 0x20);
            break;
        case 2:
            f4 = (u8) (f4 | 0x30);
            break;
        case 0x38:
            break;
    }

    func_ov003_02217c14(p8f0, f4, f1, f2, f3);
    func_0200f328(self, 0x4f);
}
