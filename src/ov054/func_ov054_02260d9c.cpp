/* func_ov054_02260d9c @ 0x02260d9c, 0xbc bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov054_0226300419func_ov054_02260d9cEj
 */

#include "cpp/ov054/Obj_ov054_02263004.h"

typedef unsigned int u32;
typedef void (Obj_ov054_02263004::*PMF)(u32);

struct Entry {
    u32 a, b, c;
};

extern Entry data_ov054_02262fac[];
extern "C" void *strlen(void *p);
extern "C" void *strncmp(void *p, void *q, void *r);
extern "C" int func_020a12e8(void);

void Obj_ov054_02263004::func_ov054_02260d9c(u32 arg2)
{
    static PMF table[3] = {&Obj_ov054_02263004::func_ov054_02260c00, &Obj_ov054_02263004::func_ov054_02260b70,
                           &Obj_ov054_02263004::func_ov054_02260b30};

    u32 idx = *(u32 *) (unk_B0 + 0x808);
    void *val = (void *) data_ov054_02262fac[idx].a;

    val = strncmp(name, val, strlen(val));

    int result;
    if (func_020a12e8() != 0) {
        result = 2;
    } else if (val == 0) {
        result = 0;
    } else {
        result = 1;
    }

    (this->*table[result])(arg2);
}
