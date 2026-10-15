/* func_ov046_02260ebc @ 0x02260ebc, 0x240 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov046_0226204c19func_ov046_02260ebcEv
 */

#include "cpp/ov046/Obj_ov046_0226204c.h"

typedef void (Obj_ov046_0226204c::*PMF)();

struct E {
    int key;
    PMF fn;
};

extern "C" int func_020a12e8(void);
extern "C" int func_020984e8(void);
extern "C" void func_0206844c(int, unsigned char *, void *);
extern void *data_ov046_02261fe8;

void Obj_ov046_0226204c::func_ov046_02260ebc()
{
    unsigned int i;
    unsigned char *q;
    int k;
    unsigned char c;

    if (func_020a12e8()) {
        return;
    }
    func_020984e8();
    next = 0xff;
    {
        static E tbl[29] = {{0, &Obj_ov046_0226204c::func_ov046_02260e34},    {4, &Obj_ov046_0226204c::func_ov046_02260ddc},
                            {5, &Obj_ov046_0226204c::func_ov046_02260d18},    {7, &Obj_ov046_0226204c::func_ov046_02260d98},
                            {9, &Obj_ov046_0226204c::func_ov046_02260d18},    {0xb, &Obj_ov046_0226204c::func_ov046_02260d64},
                            {0xc, &Obj_ov046_0226204c::func_ov046_02260d50},  {0x12, &Obj_ov046_0226204c::func_ov046_02260d50},
                            {0x15, &Obj_ov046_0226204c::func_ov046_02260d3c}, {0x16, &Obj_ov046_0226204c::func_ov046_02260d50},
                            {0x17, &Obj_ov046_0226204c::func_ov046_02260d50}, {0x1a, &Obj_ov046_0226204c::func_ov046_02260d50},
                            {0x1b, &Obj_ov046_0226204c::func_ov046_02260d50}, {0x1d, &Obj_ov046_0226204c::func_ov046_02260d50},
                            {0x1e, &Obj_ov046_0226204c::func_ov046_02260d3c}, {0x1f, &Obj_ov046_0226204c::func_ov046_02260d3c},
                            {0x21, &Obj_ov046_0226204c::func_ov046_02260d50}, {0x2c, &Obj_ov046_0226204c::func_ov046_02260e34},
                            {0x2d, &Obj_ov046_0226204c::func_ov046_02260e34}, {0x2e, &Obj_ov046_0226204c::func_ov046_02260e34},
                            {0x30, &Obj_ov046_0226204c::func_ov046_02260cd0}, {0x32, &Obj_ov046_0226204c::func_ov046_02260d50},
                            {0x33, &Obj_ov046_0226204c::func_ov046_02260d50}, {0x3b, &Obj_ov046_0226204c::func_ov046_02260cf4},
                            {0x3d, &Obj_ov046_0226204c::func_ov046_02260d50}, {0x3e, &Obj_ov046_0226204c::func_ov046_02260d50},
                            {0x3f, &Obj_ov046_0226204c::func_ov046_02260d3c}, {0x40, &Obj_ov046_0226204c::func_ov046_02260d3c},
                            {0x41, &Obj_ov046_0226204c::func_ov046_02260d3c}};
        i = 0;
        q = &mode;
        goto test;
    body:
        k = tbl[i].key;
        if (k == *q) {
            (this->*((E *) ((char *) tbl + i * sizeof(E)))->fn)();
        }
        i++;
    test:
        if (i < 29) {
            goto body;
        }
    }
    if (next != 0xff) {
        c = (unsigned char) next;
        func_0206844c(unk_40, &c, &data_ov046_02261fe8);
    }
}
