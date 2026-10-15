/* func_020058e4 @ 0x020058e4, 0xbe8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020d82b4.h"

typedef void (Obj_020d82b4::*PMF)();

struct UnkStruct_020058e4;

extern "C" int func_0203f8d0(Vec_0203f080 *, Vec_0203f080 *);
extern "C" void func_020103e4(Obj_020d82b4 *);
extern "C" void func_02010134(Obj_020d82b4 *);
extern "C" int func_02073908(UnkStruct_020058e4 *, int);
extern "C" void func_0200dc98(Obj_020d82b4 *);
extern "C" int func_0200dc8c(Obj_020d82b4 *);
extern "C" int func_0200f290(Obj_020d82b4 *, int);
extern "C" void func_020069f0(Obj_020d82b4 *);
extern "C" void func_02006554(Obj_020d82b4 *);
extern "C" void func_0205ea60(Member_0205ef90 *member);
extern "C" void func_02010f48(Obj_020d82b4 *);
extern "C" int func_02011520(int);
extern "C" void func_02006530(Obj_020d82b4 *, int, int);
extern "C" void func_020064f0(Obj_020d82b4 *, int);
extern "C" void func_020082ac(Obj_020d82b4 *);
extern "C" void func_02010424(Obj_020d82b4 *);
extern "C" void func_02010160(Obj_020d82b4 *);
extern "C" void func_ov003_0220cd84(Obj_020d82b4 *);
extern "C" void func_ov003_0220cd08(Obj_020d82b4 *);
extern "C" void func_ov003_0220cc24(Obj_020d82b4 *);
extern "C" void func_ov003_0220ca24(Obj_020d82b4 *);
extern "C" void func_0200fef0(Obj_020d82b4 *);
extern "C" int func_0200fea0(Obj_020d82b4 *);
extern "C" void func_ov003_0220cbb4(Obj_020d82b4 *);
extern "C" void func_0200f098(Obj_020d82b4 *);
extern "C" void func_020044d0(Obj_0213f058 *member, int *pos);
extern "C" void func_02004444(Obj_020d8414 *member, int *pos);

extern UnkStruct_020058e4 *data_020ccf94;
extern unsigned char data_020e54a8;

#define TABLE                                                                                                                 \
    static PMF tbl[147] = {                                                                                                   \
        &Obj_020d82b4::func_0200d58c,       &Obj_020d82b4::func_0200d52c,       &Obj_020d82b4::func_0200d1e4,                 \
        &Obj_020d82b4::func_0200cc44,       &Obj_020d82b4::func_0200c9ec,       &Obj_020d82b4::func_0200c954,                 \
        &Obj_020d82b4::func_ov003_02218ff0, &Obj_020d82b4::func_0200c3f4,       &Obj_020d82b4::func_ov004_0222bc28,           \
        &Obj_020d82b4::func_ov004_0222ba24, &Obj_020d82b4::func_ov004_0222b6ec, &Obj_020d82b4::func_ov004_0222b524,           \
        &Obj_020d82b4::func_ov004_0222b42c, &Obj_020d82b4::func_ov004_0222b288, &Obj_020d82b4::func_ov004_0222afd0,           \
        &Obj_020d82b4::func_ov004_0222ad28, &Obj_020d82b4::func_0200c200,       &Obj_020d82b4::func_ov003_02218f18,           \
        &Obj_020d82b4::func_ov004_0222ac80, &Obj_020d82b4::func_0200c120,       &Obj_020d82b4::func_0200bef0,                 \
        &Obj_020d82b4::func_0200be18,       &Obj_020d82b4::func_ov003_02218cec, &Obj_020d82b4::func_ov003_02218920,           \
        &Obj_020d82b4::func_0200b8b4,       &Obj_020d82b4::func_0200ad8c,       &Obj_020d82b4::func_0200a6fc,                 \
        &Obj_020d82b4::func_0200a4b8,       &Obj_020d82b4::func_ov004_0222a4e4, &Obj_020d82b4::func_ov004_0222a28c,           \
        &Obj_020d82b4::func_ov004_02229f60, &Obj_020d82b4::func_ov004_02229d5c, &Obj_020d82b4::func_ov004_02229bec,           \
        &Obj_020d82b4::func_ov004_02229a7c, &Obj_020d82b4::func_ov004_02229960, &Obj_020d82b4::func_ov004_022297d8,           \
        &Obj_020d82b4::func_ov004_02229510, &Obj_020d82b4::func_ov004_022292c8, &Obj_020d82b4::func_ov004_02229080,           \
        &Obj_020d82b4::func_ov004_02228e38, &Obj_020d82b4::func_ov004_02228c18, &Obj_020d82b4::func_ov004_02228b4c,           \
        &Obj_020d82b4::func_ov004_02228a80, &Obj_020d82b4::func_ov004_02228888, &Obj_020d82b4::func_ov004_02228690,           \
        &Obj_020d82b4::func_ov004_02228410, &Obj_020d82b4::func_ov004_02228304, &Obj_020d82b4::func_ov004_02228170,           \
        &Obj_020d82b4::func_0200a338,       &Obj_020d82b4::func_0200a28c,       &Obj_020d82b4::func_02009fe4,                 \
        &Obj_020d82b4::func_02009f2c,       &Obj_020d82b4::func_02009e88,       &Obj_020d82b4::func_02009d74,                 \
        &Obj_020d82b4::func_ov004_0222801c, &Obj_020d82b4::func_ov004_02227f08, &Obj_020d82b4::func_ov003_02218734,           \
        &Obj_020d82b4::func_ov003_0221842c, &Obj_020d82b4::func_ov003_022183c8, &Obj_020d82b4::func_ov003_02217e14,           \
        &Obj_020d82b4::func_ov003_02217d38, &Obj_020d82b4::func_ov003_022178b0, &Obj_020d82b4::func_ov003_02217488,           \
        &Obj_020d82b4::func_02009ab4,       &Obj_020d82b4::func_ov004_022279d8, &Obj_020d82b4::func_ov004_022277cc,           \
        &Obj_020d82b4::func_ov004_022275d8, &Obj_020d82b4::func_ov004_022274a0, &Obj_020d82b4::func_ov004_02227368,           \
        &Obj_020d82b4::func_ov003_022172c4, &Obj_020d82b4::func_ov003_02216eec, &Obj_020d82b4::func_ov003_02216bfc,           \
        &Obj_020d82b4::func_ov003_02216b18, &Obj_020d82b4::func_ov003_022166f8, &Obj_020d82b4::func_ov003_0221646c,           \
        &Obj_020d82b4::func_ov003_0221615c, &Obj_020d82b4::func_ov003_02215f58, &Obj_020d82b4::func_ov003_02215d1c,           \
        &Obj_020d82b4::func_ov003_02215bf8, &Obj_020d82b4::func_ov003_02215798, &Obj_020d82b4::func_ov003_02215668,           \
        &Obj_020d82b4::func_ov003_022154cc, &Obj_020d82b4::func_ov003_02215394, &Obj_020d82b4::func_ov003_0221527c,           \
        &Obj_020d82b4::func_ov003_02214c40, &Obj_020d82b4::func_ov003_022146bc, &Obj_020d82b4::func_ov003_02213b28,           \
        &Obj_020d82b4::func_ov003_0221320c, &Obj_020d82b4::func_ov003_02212d0c, &Obj_020d82b4::func_ov003_02212884,           \
        &Obj_020d82b4::func_ov003_022124c4, &Obj_020d82b4::func_ov003_022123e0, &Obj_020d82b4::func_ov003_02212308,           \
        &Obj_020d82b4::func_ov003_02211db0, &Obj_020d82b4::func_ov003_022119f0, &Obj_020d82b4::func_ov003_02210fa0,           \
        &Obj_020d82b4::func_ov003_02210c70, &Obj_020d82b4::func_ov003_02210a44, &Obj_020d82b4::func_ov003_022106a4,           \
        &Obj_020d82b4::func_ov003_0221038c, &Obj_020d82b4::func_ov003_0221018c, &Obj_020d82b4::func_ov003_02210120,           \
        &Obj_020d82b4::func_ov003_0220fe04, &Obj_020d82b4::func_ov003_0220fb94, &Obj_020d82b4::func_ov003_0220f7cc,           \
        &Obj_020d82b4::func_ov003_0220f590, &Obj_020d82b4::func_ov003_0220f410, &Obj_020d82b4::func_ov003_0220f37c,           \
        &Obj_020d82b4::func_ov003_0220f280, &Obj_020d82b4::func_ov003_0220f000, &Obj_020d82b4::func_ov003_0220ee04,           \
        &Obj_020d82b4::func_020095f4,       &Obj_020d82b4::func_020094e4,       &Obj_020d82b4::func_ov003_0220ea78,           \
        &Obj_020d82b4::func_ov003_0220e938, &Obj_020d82b4::func_ov003_0220e600, &Obj_020d82b4::func_ov003_0220e228,           \
        &Obj_020d82b4::func_ov003_0220e0a8, &Obj_020d82b4::func_02008dfc,       &Obj_020d82b4::func_02008c8c,                 \
        &Obj_020d82b4::func_ov003_0220dde8, &Obj_020d82b4::func_02008a8c,       &Obj_020d82b4::func_ov004_02227254,           \
        &Obj_020d82b4::func_ov004_02227190, &Obj_020d82b4::func_ov004_02226fdc, &Obj_020d82b4::func_ov004_02226eb0,           \
        &Obj_020d82b4::func_ov004_02226e34, &Obj_020d82b4::func_ov004_02226d4c, &Obj_020d82b4::func_ov003_0220dbec,           \
        &Obj_020d82b4::func_ov003_0220d8f4, &Obj_020d82b4::func_ov003_0220d6d4, &Obj_020d82b4::func_02008970,                 \
        &Obj_020d82b4::func_020087a0,       &Obj_020d82b4::func_02008490,       &Obj_020d82b4::func_020083bc,                 \
        &Obj_020d82b4::func_ov068_02271ed0, &Obj_020d82b4::func_ov068_02271dd4, &Obj_020d82b4::func_ov003_0220d4dc,           \
        &Obj_020d82b4::func_ov004_02226c80, &Obj_020d82b4::func_ov004_02226890, &Obj_020d82b4::func_ov004_02226630,           \
        &Obj_020d82b4::func_ov004_022264a8, &Obj_020d82b4::func_ov004_0222629c, &Obj_020d82b4::func_ov003_0220d2a4,           \
        &Obj_020d82b4::func_02008304,       &Obj_020d82b4::func_020082f4,       &Obj_020d82b4::func_020082e8,                 \
    };

extern "C" void func_020058e4(Obj_020d82b4 *self)
{
    UnkStruct_020058e4 *g;
    Vec_0203f080 tmp;
    int k;
    int fl;

    fl = self->unk_B0;
    if ((fl & 4) ? 1 : 0) {
        if ((fl & 2) ? 1 : 0) {
            Vec_0203f080 *p = &self->unk_5C;
            tmp = *p;
            self->unk_6F4 = p->x;
            self->unk_6F8 = p->y;
            self->unk_6FC = p->z;
            {
                Vec_0203f080 *q = (Vec_0203f080 *) &self->unk_6F4;
                self->unk_6E0 = q->x;
                self->unk_6E4 = q->y;
                self->unk_6E8 = q->z;
                {
                    Vec_0203f080 *r = (Vec_0203f080 *) &self->unk_6E0;
                    self->unk_6D4 = r->x;
                    self->unk_6D8 = r->y;
                    self->unk_6DC = r->z;
                    {
                        Vec_0203f080 *s = (Vec_0203f080 *) &self->unk_6D4;
                        self->unk_6C8 = s->x;
                        self->unk_6CC = s->y;
                        self->unk_6D0 = s->z;
                    }
                }
            }
            func_0203f8d0(&tmp, &tmp);
            self->unk_65C = tmp.x;
            self->unk_62C = self->unk_65C;
            self->unk_6BC = self->unk_62C;
            self->unk_68C = self->unk_6BC;
            self->unk_660 = tmp.y;
            self->unk_630 = self->unk_660;
            self->unk_6C0 = self->unk_630;
            self->unk_690 = self->unk_6C0;
            self->unk_664 = tmp.z;
            self->unk_634 = self->unk_664;
            self->unk_6C4 = self->unk_634;
            self->unk_694 = self->unk_6C4;
        }
    }
    func_020103e4(self);
    func_02010134(self);
    g = data_020ccf94;
    if (func_02073908(g, self->unk_800)) {
        func_0200dc98(self);
        if (func_0200dc8c(self) == 0) {
            self->unk_8EA = 0;
        }
    } else if (func_0200f290(self, 0x10) == 0) {
        func_020069f0(self);
    }
    func_02006554(self);
    func_0205ea60(&self->unk_5A0);
    self->unk_8C4 = 0;
    self->unk_8C8 = 0;
    self->unk_8CC = 0;
    {
        TABLE
        PMF f;

        f = tbl[self->unk_7F0];
        func_02010f48(self);
        (self->*f)();
    }
    func_02011520(self->unk_800);
    k = self->unk_7F0;
    func_02006530(self, k, 0);
    if (func_02073908(g, self->unk_800)) {
        func_020064f0(self, k);
    }
    func_020082ac(self);
    func_02010424(self);
    func_02010160(self);
    if (func_02073908(g, self->unk_800)) {
        if (data_020e54a8 ? 0 : 1) {
            func_ov003_0220cd84(self);
            func_ov003_0220cd08(self);
            func_ov003_0220cc24(self);
            func_ov003_0220ca24(self);
        }
        if (self->unk_8E8) {
            self->unk_8E8--;
        }
    }
    if (self->unk_8EC) {
        self->unk_8EC--;
    }
    func_0200fef0(self);
    self->unk_818 = func_0200fea0(self);
    if (func_02073908(g, self->unk_800)) {
        if (data_020e54a8 ? 0 : 1) {
            func_ov003_0220cbb4(self);
        }
    }
    func_0200f098(self);
    if (func_0200f290(self, 0xa)) {
        if (self->unk_8C4 == 0 && self->unk_8C8 == 0 && self->unk_8CC == 0) {
            self->unk_8C4 = self->unk_5C.x;
            self->unk_8C8 = self->unk_5C.y;
            self->unk_8CC = self->unk_5C.z;
        }
        if (func_0200f290(self, 0x19)) {
            func_020044d0(&self->unk_83C, &self->unk_8C4);
        } else {
            func_02004444(&self->unk_880, &self->unk_8C4);
        }
    }
    {
        int cur = *(volatile int *) &self->unk_7F4;
        if (cur != self->unk_7F0) {
            self->unk_7F4 = self->unk_7F0;
        }
    }
}
