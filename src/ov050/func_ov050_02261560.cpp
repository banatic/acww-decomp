/* func_ov050_02261560 @ 0x02261560, 0x2d0 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov050_02265b1419func_ov050_02261560Ei
 */

#include "cpp/ov050/Obj_ov050_02265b14.h"

typedef void (Obj_ov050_02265b14::*PMF)(int);

struct E {
    int key;
    PMF fn;
};

extern "C" void func_020160b4(void);
extern "C" int func_020ab504(void);
extern "C" int func_ov050_02260510(int);
extern "C" void func_0206844c(int, unsigned char *, void *);

extern void *data_ov050_02265824;
extern void *data_ov050_02265804;

void Obj_ov050_02265b14::func_ov050_02261560(int arg)
{
    unsigned int i;
    unsigned char *q;
    int k;
    int r;
    unsigned char c;
    void *s;

    func_020160b4();
    r = func_020ab504();
    unk_D0 = 0xff;
    {
        static E tbl[37] = {{0, &Obj_ov050_02265b14::func_ov050_022614c8},    {2, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {5, &Obj_ov050_02265b14::func_ov050_02261494},    {6, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {8, &Obj_ov050_02265b14::func_ov050_022614c8},    {0xa, &Obj_ov050_02265b14::func_ov050_02261480},
                            {0xb, &Obj_ov050_02265b14::func_ov050_022614c8},  {0xc, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {0xe, &Obj_ov050_02265b14::func_ov050_022610b0},  {0xf, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {0x11, &Obj_ov050_02265b14::func_ov050_022610b0}, {0x12, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {0x17, &Obj_ov050_02265b14::func_ov050_022614c8}, {0x19, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {0x1a, &Obj_ov050_02265b14::func_ov050_022613d8}, {0x1b, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {0x1c, &Obj_ov050_02265b14::func_ov050_022614c8}, {0x1d, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {0x1e, &Obj_ov050_02265b14::func_ov050_02261390}, {0x2a, &Obj_ov050_02265b14::func_ov050_02261390},
                            {0x2b, &Obj_ov050_02265b14::func_ov050_02261200}, {0x2c, &Obj_ov050_02265b14::func_ov050_022612f4},
                            {0x2e, &Obj_ov050_02265b14::func_ov050_02261174}, {0x31, &Obj_ov050_02265b14::func_ov050_02261390},
                            {0x35, &Obj_ov050_02265b14::func_ov050_02261138}, {0x40, &Obj_ov050_02265b14::func_ov050_022610b0},
                            {0x42, &Obj_ov050_02265b14::func_ov050_02261094}, {0x43, &Obj_ov050_02265b14::func_ov050_02261094},
                            {0x44, &Obj_ov050_02265b14::func_ov050_02261078}, {0x45, &Obj_ov050_02265b14::func_ov050_0226105c},
                            {0x46, &Obj_ov050_02265b14::func_ov050_02261040}, {0x47, &Obj_ov050_02265b14::func_ov050_02261094},
                            {0x55, &Obj_ov050_02265b14::func_ov050_02261094}, {0x56, &Obj_ov050_02265b14::func_ov050_02261094},
                            {0x58, &Obj_ov050_02265b14::func_ov050_022614c8}, {0x59, &Obj_ov050_02265b14::func_ov050_022614c8},
                            {0x5d, &Obj_ov050_02265b14::func_ov050_022614c8}};
        i = 0;
        q = &unk_1E;
        goto test;
    body:
        k = tbl[i].key;
        if (k == *q) {
            (this->*((E *) ((char *) tbl + i * sizeof(E)))->fn)(r);
        }
        i++;
    test:
        if (i < 37) {
            goto body;
        }
    }
    if (unk_D0 != 0xff) {
        s = func_ov050_02260510(unk_B4) ? &data_ov050_02265824 : &data_ov050_02265804;
        c = (unsigned char) unk_D0;
        func_0206844c(unk_40, &c, s);
    }
}
