/* func_ov051_02260928 @ 0x02260928, 0x238 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov051_0226180419func_ov051_02260928Ev
 */

#include "cpp/ov051/Obj_ov051_02261804.h"

typedef void (Obj_ov051_02261804::*PMF)();

struct E {
    int key;
    PMF fn;
};

void Obj_ov051_02261804::func_ov051_02260928()
{
    unsigned int i;
    unsigned char *q;
    int k;

    {
        static E tbl[32] = {
            {1, &Obj_ov051_02261804::func_ov051_02260e08},    {4, &Obj_ov051_02261804::func_ov051_02260e08},
            {8, &Obj_ov051_02261804::func_ov051_02260de4},    {0xa, &Obj_ov051_02261804::func_ov051_02260de4},
            {0x29, &Obj_ov051_02261804::func_ov051_02260de4}, {0xf, &Obj_ov051_02261804::func_ov051_02260dc0},
            {0x10, &Obj_ov051_02261804::func_ov051_02260dc0}, {0x13, &Obj_ov051_02261804::func_ov051_02260dc0},
            {0x14, &Obj_ov051_02261804::func_ov051_02260dc0}, {0x25, &Obj_ov051_02261804::func_ov051_02260b60},
            {0x26, &Obj_ov051_02261804::func_ov051_02260b60}, {6, &Obj_ov051_02261804::func_ov051_02260d94},
            {7, &Obj_ov051_02261804::func_ov051_02260d94},    {0x1b, &Obj_ov051_02261804::func_ov051_02260d44},
            {0x1c, &Obj_ov051_02261804::func_ov051_02260d44}, {0x1d, &Obj_ov051_02261804::func_ov051_02260d44},
            {0x1e, &Obj_ov051_02261804::func_ov051_02260d44}, {0x2b, &Obj_ov051_02261804::func_ov051_02260d1c},
            {0x2c, &Obj_ov051_02261804::func_ov051_02260d1c}, {0x2d, &Obj_ov051_02261804::func_ov051_02260d1c},
            {0x2e, &Obj_ov051_02261804::func_ov051_02260d1c}, {0xd, &Obj_ov051_02261804::func_ov051_02260cd8},
            {0xe, &Obj_ov051_02261804::func_ov051_02260c94},  {0x17, &Obj_ov051_02261804::func_ov051_02260c44},
            {0x18, &Obj_ov051_02261804::func_ov051_02260c44}, {0x21, &Obj_ov051_02261804::func_ov051_02260c1c},
            {0x22, &Obj_ov051_02261804::func_ov051_02260c1c}, {0x23, &Obj_ov051_02261804::func_ov051_02260c1c},
            {0x24, &Obj_ov051_02261804::func_ov051_02260c1c}, {0x2f, &Obj_ov051_02261804::func_ov051_02260c1c},
            {0x31, &Obj_ov051_02261804::func_ov051_02260c1c}, {0x32, &Obj_ov051_02261804::func_ov051_02260c1c}};
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
        if (i < 32) {
            goto body;
        }
    }
}
