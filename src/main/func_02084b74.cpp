/* func_02084b74 @ 0x02084b74, 0xec bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02084b74;

typedef void (UnkStruct_02084b74::*PMF)(void *, void *, void *);

struct UnkStruct_02084b74_2 {
    u16 a, b, c;
};
struct UnkStruct_02084b74_3 {
    int a, b, c;
};

struct UnkStruct_02084b74_4 {
    u8 pad_00[0xe];
    u8 unk_0E;
    u8 pad_0F;
};
struct Ctx2 {
    int pad_00;
};

struct Entry {
    u16 unk_00;
    u16 unk_02;
    int unk_04;
    PMF fn;
    u8 f10 : 1;
};

struct Glob {
    u8 pad_00[0x64];
    int unk_64;
};

extern UnkStruct_02084b74_4 data_020e1ca8;
extern Ctx2 data_020e1cb4;
extern u8 data_020e54a8;
extern Glob *data_020ccf94;

extern "C" int func_02084d9c(UnkStruct_02084b74 *self, UnkStruct_02084b74_4 *c);
extern "C" Entry *func_02084d34(Ctx2 *c, int a, int b);
extern "C" int func_020b65c4(void);
extern "C" int func_0204f934(int a);
extern "C" void func_02084d8c(UnkStruct_02084b74 *self, int *p);
extern "C" void func_02084d84(UnkStruct_02084b74 *self);
extern "C" int func_02003348(int a, int b, void *v, void *s, UnkStruct_02084b74 *self);
extern "C" int func_02073dd4(Glob *g, int a);
extern "C" void func_02042fd4(UnkStruct_02084b74_3 *v);
extern "C" void func_02084dac(UnkStruct_02084b74_4 *c);

extern "C" Entry *func_02084b74(UnkStruct_02084b74 *self, int a, int b)
{
    Entry *result = 0;
    UnkStruct_02084b74_2 s;
    UnkStruct_02084b74_3 v;
    UnkStruct_02084b74_3 v2;
    Entry *e;
    unsigned int ok;

    if (func_02084d9c(self, &data_020e1ca8) != 0) {
        e = func_02084d34(&data_020e1cb4, a, b);
        if (e != 0) {
            if (data_020e1ca8.unk_0E == func_020b65c4()) {
                s.a = 0;
                s.b = 0;
                s.c = 0;
                if (e->fn) {
                    (self->*(e->fn))(&v, &s, &data_020e1ca8);
                }
                if (e->f10) {
                    func_0204f934(e->unk_04);
                    func_02084d8c(self, &e->unk_04);
                } else {
                    func_02084d84(self);
                }
                if (func_02003348(e->unk_00, e->unk_02, &v, &s, self) != 0) {
                    if (data_020e54a8 == 0) {
                        ok = 1;
                    } else {
                        ok = 0;
                    }
                    if (ok != 0) {
                        if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
                            v2 = v;
                            func_02042fd4(&v2);
                        }
                    }
                    result = e;
                }
            }
        }
        func_02084dac(&data_020e1ca8);
    }
    return result;
}
