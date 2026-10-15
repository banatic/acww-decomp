/* func_02007364 @ 0x02007364, 0x980 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020d82b4.h"

typedef void (Obj_020d82b4::*PMF)(Msg_02007364 *, int);

struct UnkStruct_02007364 {
    char cpad[0x64];
    int unk_64;
};

extern "C" void func_02007d40(Obj_020d82b4 *, int);
extern "C" void func_02007d2c(Obj_020d82b4 *);
extern "C" void func_02007d00(Obj_020d82b4 *, int);
extern "C" int func_02008270(Obj_020d82b4 *, int, int);
extern "C" void func_02007ce4(Obj_020d82b4 *, int);
extern "C" void func_02010e48(Obj_020d82b4 *, int *);
extern "C" void func_020064cc(Obj_020d82b4 *, int);
extern "C" int func_02073dd4(UnkStruct_02007364 *, int);
extern "C" int func_02073908(UnkStruct_02007364 *, int);
extern "C" short func_02073d80(UnkStruct_02007364 *);
extern "C" int func_02008264(Obj_020d82b4 *, int);
extern "C" unsigned int *func_0200f27c(Obj_020d82b4 *, int);
extern "C" void func_0200f268(Obj_020d82b4 *, int);

extern UnkStruct_02007364 *data_020ccf94;
extern void *data_020c7e48[];

#define TABLE                                                                                                                 \
    static PMF tbl[147] = {                                                                                                   \
        &Obj_020d82b4::func_0200db88,       &Obj_020d82b4::func_0200d548,       &Obj_020d82b4::func_0200d48c,                 \
        &Obj_020d82b4::func_0200d148,       &Obj_020d82b4::func_0200cac0,       &Obj_020d82b4::func_0200c98c,                 \
        &Obj_020d82b4::func_ov003_022194a8, &Obj_020d82b4::func_0200c80c,       &Obj_020d82b4::func_ov004_0222bd6c,           \
        &Obj_020d82b4::func_ov004_0222bb0c, &Obj_020d82b4::func_ov004_0222b8bc, &Obj_020d82b4::func_ov004_0222b5e0,           \
        &Obj_020d82b4::func_ov004_0222b494, &Obj_020d82b4::func_ov004_0222b31c, &Obj_020d82b4::func_ov004_0222b0fc,           \
        &Obj_020d82b4::func_ov004_0222aea4, &Obj_020d82b4::func_0200c37c,       &Obj_020d82b4::func_ov003_02218f94,           \
        &Obj_020d82b4::func_ov004_0222acc4, &Obj_020d82b4::func_0200c1a4,       &Obj_020d82b4::func_0200c050,                 \
        &Obj_020d82b4::func_0200bea4,       &Obj_020d82b4::func_ov003_02218e4c, &Obj_020d82b4::func_ov003_02218c28,           \
        &Obj_020d82b4::func_0200bc38,       &Obj_020d82b4::func_0200b428,       &Obj_020d82b4::func_0200ab44,                 \
        &Obj_020d82b4::func_0200a5f8,       &Obj_020d82b4::func_ov004_0222aa90, &Obj_020d82b4::func_ov004_0222a404,           \
        &Obj_020d82b4::func_ov004_0222a1ac, &Obj_020d82b4::func_ov004_02229e74, &Obj_020d82b4::func_ov004_02229d04,           \
        &Obj_020d82b4::func_ov004_02229b94, &Obj_020d82b4::func_ov004_022299fc, &Obj_020d82b4::func_ov004_022298e0,           \
        &Obj_020d82b4::func_ov004_02229678, &Obj_020d82b4::func_ov004_022293b8, &Obj_020d82b4::func_ov004_02229170,           \
        &Obj_020d82b4::func_ov004_02228f28, &Obj_020d82b4::func_ov004_02228dc4, &Obj_020d82b4::func_ov004_02228bac,           \
        &Obj_020d82b4::func_ov004_02228ae0, &Obj_020d82b4::func_ov004_022289b8, &Obj_020d82b4::func_ov004_022287e4,           \
        &Obj_020d82b4::func_ov004_02228570, &Obj_020d82b4::func_ov004_02228344, &Obj_020d82b4::func_ov004_0222820c,           \
        &Obj_020d82b4::func_0200a3ac,       &Obj_020d82b4::func_0200a2e4,       &Obj_020d82b4::func_0200a22c,                 \
        &Obj_020d82b4::func_02009f98,       &Obj_020d82b4::func_02009ed8,       &Obj_020d82b4::func_02009e28,                 \
        &Obj_020d82b4::func_ov004_022280b0, &Obj_020d82b4::func_ov004_02227f90, &Obj_020d82b4::func_ov003_02218844,           \
        &Obj_020d82b4::func_ov003_022185b0, &Obj_020d82b4::func_ov003_022183d8, &Obj_020d82b4::func_ov003_02218210,           \
        &Obj_020d82b4::func_ov003_02217d60, &Obj_020d82b4::func_ov003_02217adc, &Obj_020d82b4::func_ov003_02217678,           \
        &Obj_020d82b4::func_02009c74,       &Obj_020d82b4::func_ov004_02227d80, &Obj_020d82b4::func_ov004_02227958,           \
        &Obj_020d82b4::func_ov004_02227764, &Obj_020d82b4::func_ov004_02227580, &Obj_020d82b4::func_ov004_02227448,           \
        &Obj_020d82b4::func_ov003_0221740c, &Obj_020d82b4::func_ov003_022170a4, &Obj_020d82b4::func_ov003_02216ea0,           \
        &Obj_020d82b4::func_ov003_02216bb0, &Obj_020d82b4::func_ov003_02216a00, &Obj_020d82b4::func_ov003_02216644,           \
        &Obj_020d82b4::func_ov003_02216390, &Obj_020d82b4::func_ov003_0221608c, &Obj_020d82b4::func_ov003_02215e78,           \
        &Obj_020d82b4::func_ov003_02215cbc, &Obj_020d82b4::func_ov003_02215af0, &Obj_020d82b4::func_ov003_02215718,           \
        &Obj_020d82b4::func_ov003_02215570, &Obj_020d82b4::func_ov003_02215460, &Obj_020d82b4::func_ov003_022152f8,           \
        &Obj_020d82b4::func_ov003_02215190, &Obj_020d82b4::func_ov003_02214bc8, &Obj_020d82b4::func_ov003_02214604,           \
        &Obj_020d82b4::func_ov003_02213988, &Obj_020d82b4::func_ov003_02213114, &Obj_020d82b4::func_ov003_02212afc,           \
        &Obj_020d82b4::func_ov003_022127a0, &Obj_020d82b4::func_ov003_02212478, &Obj_020d82b4::func_ov003_02212394,           \
        &Obj_020d82b4::func_ov003_0221220c, &Obj_020d82b4::func_ov003_02211cc0, &Obj_020d82b4::func_ov003_02211604,           \
        &Obj_020d82b4::func_ov003_02210ef8, &Obj_020d82b4::func_ov003_02210b3c, &Obj_020d82b4::func_ov003_02210950,           \
        &Obj_020d82b4::func_ov003_02210640, &Obj_020d82b4::func_ov003_022102dc, &Obj_020d82b4::func_ov003_02210140,           \
        &Obj_020d82b4::func_ov003_02210010, &Obj_020d82b4::func_ov003_0220fd04, &Obj_020d82b4::func_ov003_0220fa5c,           \
        &Obj_020d82b4::func_ov003_0220f6dc, &Obj_020d82b4::func_ov003_0220f4a8, &Obj_020d82b4::func_ov003_0220f39c,           \
        &Obj_020d82b4::func_ov003_0220f2f8, &Obj_020d82b4::func_ov003_0220f180, &Obj_020d82b4::func_ov003_0220ef80,           \
        &Obj_020d82b4::func_02009918,       &Obj_020d82b4::func_0200956c,       &Obj_020d82b4::func_ov003_0220ed30,           \
        &Obj_020d82b4::func_ov003_0220ea10, &Obj_020d82b4::func_ov003_0220e860, &Obj_020d82b4::func_ov003_0220e548,           \
        &Obj_020d82b4::func_ov003_0220e128, &Obj_020d82b4::func_0200934c,       &Obj_020d82b4::func_02008d5c,                 \
        &Obj_020d82b4::func_ov003_0220e008, &Obj_020d82b4::func_02008bf4,       &Obj_020d82b4::func_ov004_022272f4,           \
        &Obj_020d82b4::func_ov004_022271e0, &Obj_020d82b4::func_ov004_02227118, &Obj_020d82b4::func_ov004_02226f4c,           \
        &Obj_020d82b4::func_ov004_02226e5c, &Obj_020d82b4::func_ov004_02226db4, &Obj_020d82b4::func_ov003_0220dd9c,           \
        &Obj_020d82b4::func_ov003_0220db4c, &Obj_020d82b4::func_ov003_0220d880, &Obj_020d82b4::func_02008a38,                 \
        &Obj_020d82b4::func_02008910,       &Obj_020d82b4::func_020086c4,       &Obj_020d82b4::func_02008444,                 \
        &Obj_020d82b4::func_ov068_02271f80, &Obj_020d82b4::func_ov068_02271e7c, &Obj_020d82b4::func_ov003_0220d680,           \
        &Obj_020d82b4::func_ov004_02226d00, &Obj_020d82b4::func_ov004_02226aac, &Obj_020d82b4::func_ov004_0222671c,           \
        &Obj_020d82b4::func_ov004_0222654c, &Obj_020d82b4::func_ov004_0222631c, &Obj_020d82b4::func_ov003_0220d444,           \
        &Obj_020d82b4::func_02008364,       &Obj_020d82b4::func_02008300,       &Obj_020d82b4::func_020082f0,                 \
    };

extern "C" void func_02007364(Obj_020d82b4 *self, Msg_02007364 *msg)
{
    TABLE
    UnkStruct_02007364 *g;
    int id;
    PMF f;
    int saved;
    short h;

    id = msg->unk_00;
    h = msg->unk_08;
    f = tbl[id];
    saved = self->unk_7F4;
    func_02007d40(self, id);
    func_02007d2c(self);
    self->unk_7F0 = id;
    func_02007d00(self, id);
    func_02008270(self, id, saved);
    func_02007ce4(self, id);
    func_02010e48(self, &id);
    func_020064cc(self, id);
    g = data_020ccf94;
    if (func_02073dd4(g, g->unk_64)) {
        if (func_02073908(g, self->unk_800) == 0) {
            if (h >= 0) {
                self->unk_C84 = h;
                self->unk_C88 = id;
            }
        } else {
            self->unk_C84 = func_02073d80(g);
        }
    }
    (self->*f)(msg, saved);
    self->unk_7FC = func_02008264(self, id);
    if (func_02073908(g, self->unk_800) == 0 && data_020c7e48[id] != 0) {
        func_0200f27c(self, 0x12);
    } else {
        func_0200f268(self, 0x12);
    }
}
