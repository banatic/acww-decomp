/* func_ov046_02260abc @ 0x02260abc, 0x214 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov046_0226204c19func_ov046_02260abcEv
 */

#include "cpp/ov046/Obj_ov046_0226204c.h"

typedef void (Obj_ov046_0226204c::*PMF)(int);

struct E {
    int key;
    PMF fn;
};

extern "C" void func_0206844c(int, unsigned char *, void *);
extern void *data_ov046_02261fe8;
extern "C" int func_020ab504(void *);
extern "C" int func_020160b4(void *arg0);

void Obj_ov046_0226204c::func_ov046_02260abc()
{
    unsigned int i;
    unsigned char *q;
    int k;
    int r;
    unsigned char c;

    r = func_020ab504((void *) func_020160b4((void *) this));
    next = 0xff;
    {
        static E tbl[26] = {
            {1, &Obj_ov046_0226204c::func_ov046_0226086c},    {8, &Obj_ov046_0226204c::func_ov046_02260aa8},
            {0x10, &Obj_ov046_0226204c::func_ov046_022606f4}, {0x13, &Obj_ov046_0226204c::func_ov046_022606f4},
            {0x14, &Obj_ov046_0226204c::func_ov046_022607f0}, {0x15, &Obj_ov046_0226204c::func_ov046_02260914},
            {0x18, &Obj_ov046_0226204c::func_ov046_02260720}, {0x19, &Obj_ov046_0226204c::func_ov046_0226077c},
            {0x1e, &Obj_ov046_0226204c::func_ov046_02260914}, {0x1f, &Obj_ov046_0226204c::func_ov046_02260914},
            {0x20, &Obj_ov046_0226204c::func_ov046_022606e0}, {0x23, &Obj_ov046_0226204c::func_ov046_022608a4},
            {0x24, &Obj_ov046_0226204c::func_ov046_0226068c}, {0x25, &Obj_ov046_0226204c::func_ov046_02260720},
            {0x26, &Obj_ov046_0226204c::func_ov046_022606f4}, {0x27, &Obj_ov046_0226204c::func_ov046_022606f4},
            {0x28, &Obj_ov046_0226204c::func_ov046_022607f0}, {0x29, &Obj_ov046_0226204c::func_ov046_0226086c},
            {0x2a, &Obj_ov046_0226204c::func_ov046_02260720}, {0x2b, &Obj_ov046_0226204c::func_ov046_02260720},
            {0x31, &Obj_ov046_0226204c::func_ov046_022608e4}, {0x35, &Obj_ov046_0226204c::func_ov046_02260664},
            {0x38, &Obj_ov046_0226204c::func_ov046_02260644}, {0x3f, &Obj_ov046_0226204c::func_ov046_02260914},
            {0x40, &Obj_ov046_0226204c::func_ov046_02260914}, {0x41, &Obj_ov046_0226204c::func_ov046_02260914}};
        i = 0;
        q = &mode;
        goto test;
    body:
        k = tbl[i].key;
        if (k == *q) {
            (this->*((E *) ((char *) tbl + i * sizeof(E)))->fn)(r);
        }
        i++;
    test:
        if (i < 26) {
            goto body;
        }
    }
    if (next != 0xff) {
        c = (unsigned char) next;
        func_0206844c(unk_40, &c, &data_ov046_02261fe8);
    }
}
