/* func_ov048_02261748 @ 0x02261748, 0x224 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov048_0226420819func_ov048_02261748Ev
 */

#include "cpp/ov048/Obj_ov048_02264208.h"

typedef void (Obj_ov048_02264208::*PMF)(int);

#define DISCARD_HANDLER(Class, Method) (PMF) & Class::Method

struct E {
    int key;
    PMF fn;
};

extern "C" int func_020a12e8(void);
extern "C" unsigned int func_0206837c(int);
extern "C" int func_020ab504(void *);

void Obj_ov048_02264208::func_ov048_02261748()
{
    unsigned int i;
    unsigned char *q;
    int k;
    int r;

    if (func_020a12e8()) {
        return;
    }
    {
        static E tbl[29] = {{0x15, &Obj_ov048_02264208::func_ov048_02261b1c},
                            {0x41, DISCARD_HANDLER(Obj_ov048_02264208, func_ov048_02261b10)},
                            {0x14, DISCARD_HANDLER(Obj_ov048_02264208, func_ov048_02261b04)},
                            {0x7f, &Obj_ov048_02264208::func_ov048_02261af8},
                            {0x24, &Obj_ov048_02264208::func_ov048_02261b28},
                            {0x56, &Obj_ov048_02264208::func_ov048_02261b28},
                            {0xa, &Obj_ov048_02264208::func_ov048_02261ce4},
                            {0x10, &Obj_ov048_02264208::func_ov048_02261b54},
                            {0x21, &Obj_ov048_02264208::func_ov048_02261b54},
                            {0xf, &Obj_ov048_02264208::func_ov048_02261be8},
                            {0x22, &Obj_ov048_02264208::func_ov048_02261be8},
                            {0x51, &Obj_ov048_02264208::func_ov048_02261a38},
                            {0x63, &Obj_ov048_02264208::func_ov048_02261a14},
                            {0x65, &Obj_ov048_02264208::func_ov048_02261a14},
                            {0x7d, &Obj_ov048_02264208::func_ov048_022619f0},
                            {0x7e, &Obj_ov048_02264208::func_ov048_022619f0},
                            {0x80, &Obj_ov048_02264208::func_ov048_022619f0},
                            {0x82, &Obj_ov048_02264208::func_ov048_022619f0},
                            {0x2c, &Obj_ov048_02264208::func_ov048_022619b0},
                            {0x6b, &Obj_ov048_02264208::func_ov048_022619ac},
                            {0x5f, &Obj_ov048_02264208::func_ov048_0226196c},
                            {0x23, &Obj_ov048_02264208::func_ov048_02261e5c},
                            {0x28, &Obj_ov048_02264208::func_ov048_02261e5c},
                            {0x2f, &Obj_ov048_02264208::func_ov048_02261e5c},
                            {0x52, &Obj_ov048_02264208::func_ov048_02261e1c},
                            {0x3d, &Obj_ov048_02264208::func_ov048_02261ddc},
                            {0x71, &Obj_ov048_02264208::func_ov048_02261e78},
                            {0x74, &Obj_ov048_02264208::func_ov048_02261ee4},
                            {0x57, &Obj_ov048_02264208::func_ov048_02261ed0}};
        i = 0;
        q = &mode;
        goto test;
    body:
        k = tbl[i].key;
        if (k == *q) {
            r = func_020ab504((void *) func_0206837c(unk_40));
            (this->*((E *) ((char *) tbl + i * sizeof(E)))->fn)(r);
        }
        i++;
    test:
        if (i < 29) {
            goto body;
        }
    }
}

#undef DISCARD_HANDLER
