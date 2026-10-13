/* func_ov004_0220c50c @ 0x0220c50c, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/sp2 -O4,s
 * compiler-emitted symbol: _ZThn236_N18Obj_ov004_0224fc4c17vfunc_02066994_14Ev
 */

#include "cpp/ov004/Obj_ov004_0224fc4c.h"

extern "C" {
extern void func_020984e8(void);
extern void func_020996a0(void);
extern void *func_020adf50(void);
extern int func_020adde4(unsigned short);
extern void func_0206844c(void *a, void *b, void *c);
extern void *data_ov004_0224fbe0;

typedef struct {
    char pad_00[0x10a];
    unsigned char state;
    char pad_10B[0x21];
    void *data;
} UnkStruct_0220bfb4;
}

Obj_ov004_0224fc4c::~Obj_ov004_0224fc4c() {}

void Obj_ov004_0224fc4c::vfunc_02066994_14()
{
    UnkStruct_0220bfb4 *p = (UnkStruct_0220bfb4 *) this;

    char buf[2];
    switch (p->state) {
        case 1:
        case 2: {
            func_020984e8();
            func_020996a0();
            if (func_020adde4(*(unsigned short *) func_020adf50()) == 4) {
                buf[0] = 5;
                func_0206844c(p->data, &buf[0], data_ov004_0224fbe0);
            } else {
                buf[1] = 3;
                func_0206844c(p->data, &buf[1], data_ov004_0224fbe0);
            }
        }
    }
}
