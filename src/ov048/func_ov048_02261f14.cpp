/* func_ov048_02261f14 @ 0x02261f14, 0x200 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov048_0226420819func_ov048_02261f14Ev
 */

#include "cpp/ov048/Obj_ov048_02264208.h"

typedef void (Obj_ov048_02264208::*PMF)();

struct E {
    int key;
    PMF fn;
};

void Obj_ov048_02264208::func_ov048_02261f14()
{
    static E tbl[28] = {{0, &Obj_ov048_02264208::func_ov048_022623f0},    {4, &Obj_ov048_02264208::func_ov048_022623f0},
                        {5, &Obj_ov048_02264208::func_ov048_022623f0},    {6, &Obj_ov048_02264208::func_ov048_022623f0},
                        {7, &Obj_ov048_02264208::func_ov048_022623f0},    {0x38, &Obj_ov048_02264208::func_ov048_022623b8},
                        {0x46, &Obj_ov048_02264208::func_ov048_02262358}, {0x54, &Obj_ov048_02264208::func_ov048_022622ec},
                        {0x3e, &Obj_ov048_02264208::func_ov048_02262320}, {0x5b, &Obj_ov048_02264208::func_ov048_02262320},
                        {0x6c, &Obj_ov048_02264208::func_ov048_02262358}, {0x47, &Obj_ov048_02264208::func_ov048_02262368},
                        {0x48, &Obj_ov048_02264208::func_ov048_02262368}, {0x49, &Obj_ov048_02264208::func_ov048_02262368},
                        {0x25, &Obj_ov048_02264208::func_ov048_02262320}, {0x55, &Obj_ov048_02264208::func_ov048_022622bc},
                        {0x5d, &Obj_ov048_02264208::func_ov048_02262298}, {0x6d, &Obj_ov048_02264208::func_ov048_02262298},
                        {0x62, &Obj_ov048_02264208::func_ov048_022621e8}, {0x59, &Obj_ov048_02264208::func_ov048_0226224c},
                        {0x68, &Obj_ov048_02264208::func_ov048_022621d8}, {0xd, &Obj_ov048_02264208::func_ov048_022621c8},
                        {0x11, &Obj_ov048_02264208::func_ov048_022621a0}, {0x58, &Obj_ov048_02264208::func_ov048_022621a0},
                        {0x61, &Obj_ov048_02264208::func_ov048_022621a0}, {0x75, &Obj_ov048_02264208::func_ov048_0226213c},
                        {0x12, &Obj_ov048_02264208::func_ov048_02262114}, {0x6a, &Obj_ov048_02264208::func_ov048_0226242c}};
    unsigned int i;
    unsigned char *q;
    int k;

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
    if (i < 28) {
        goto body;
    }
}
