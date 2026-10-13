/* func_ov003_0220c934 @ 0x0220c934, 0xf0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#define IN(v, lo, hi) ((v) >= (lo) && (v) <= (hi))

class UnkStruct_0220c934 {
  public:
    virtual void o0();
    virtual void o1();
    virtual void o2();
    virtual void o3();
    virtual void o4();
    virtual void o5();
    virtual void o6();
    virtual void o7();
    virtual void o8();
    virtual void o9();
    virtual void o10();
    virtual void o11();
    virtual void o12();
    virtual void o13();
    virtual void o14();
    virtual void o15();
    virtual void o16();
    virtual void o17();
    virtual void o18();
    virtual void o19();
    virtual void o20();
    virtual void o21();
    virtual void o22();
    virtual void o23();
    virtual int o24(unsigned short *);
};

struct UnkStruct_0220c934_2 {
    char pad_00[0x168];
    UnkStruct_0220c934 *unk_168;
    u8 unk_16C;
    char pad_16D[0x1d2 - 0x16d];
    u8 unk_1D2;
    u8 unk_1D3;
    char pad_1D4[0x200 - 0x1d4];
    u8 unk_200;
};

extern "C" void func_020110c4(unsigned short *, UnkStruct_0220c934_2 *);
extern "C" UnkStruct_0220c934 *func_02082618(int, int);
extern "C" UnkStruct_0220c934 *func_ov003_02236204_unk(int);

extern "C" int func_ov003_0220c934(UnkStruct_0220c934_2 *self)
{
    unsigned short w;
    unsigned int t2;
    unsigned short wv2;
    unsigned short wv;
    unsigned int t;
    int a;
    int b;
    UnkStruct_0220c934 *p;

    self->unk_16C = 0;
    if (self->unk_200 == 0) {
        return 0;
    }
    self->unk_16C = 1;
    a = self->unk_1D2;
    b = self->unk_1D3;
    func_020110c4(&w, self);
    switch (a) {
        case 2:
        case 3:
            p = func_02082618(a, b);
            if (p != 0) {
                t = 0;
                wv = w;
                if (wv >= 0x1376 && wv <= 0x1376) {
                    t = 1;
                }
                if (t > 0 || IN(wv, 0x1377, 0x1377)) {
                    if (p->o24(&w) == 1) {
                        self->unk_16C = 4;
                        break;
                    }
                } else {
                    self->unk_168 = p;
                }
                self->unk_16C = 2;
            }
            break;
        case 0x11:
        case 0x12:
            p = func_ov003_02236204_unk(b);
            if (p != 0) {
                t2 = 0;
                wv2 = w;
                if (wv2 >= 0x1376 && wv2 <= 0x1376) {
                    t2 = 1;
                }
                if (!(t2 > 0 || IN(wv2, 0x1377, 0x1377))) {
                    self->unk_168 = p;
                }
                self->unk_16C = 3;
            }
            break;
    }
    return 1;
}
