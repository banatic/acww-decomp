/* func_ov068_0226b7c8 @ 0x0226b7c8, 0xc4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {
extern int func_020164a0(void *, int);
extern int func_02019de8(void *);
extern void func_ov068_0226cce8(void *, void *, int);
extern void *func_020800d0(void);
extern void func_0204f794(void *, int, int);

#pragma arm
extern void func_020e895c(void *, u32, u32);
#pragma thumb

extern void func_02013bb0(void *, void *);
}

class UnkStruct_0226b7c8 {
  public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual void v6() = 0;
    virtual void v7() = 0;
    virtual void v8() = 0;
    virtual void v9() = 0;
    virtual void v10() = 0;
    virtual void v11() = 0;
    virtual void v12() = 0;
    virtual void v13() = 0;
    virtual void v14() = 0;
    virtual void v15() = 0;
    virtual void v16() = 0;
    virtual void v17() = 0;
    virtual void v18() = 0;
    virtual void v19() = 0;
    virtual void v20() = 0;
    virtual void v21() = 0;
    virtual void v22() = 0;
    virtual void v23() = 0;
    virtual void v24() = 0;
    virtual void v25() = 0;
};

struct Sbits {
    unsigned char pad_00[0x190];
    unsigned int : 12;
    unsigned int mode : 16;
};

extern "C" void func_ov068_0226b7c8(void *a, UnkStruct_0226b7c8 *s)
{
    u32 out[3];
    u8 *p;
    int mode;

    if (func_020164a0((char *) s + 0x334, 0) == 0x3b) {
        if (func_02019de8((char *) s + 0x564)) {
            func_ov068_0226cce8(a, s, 3);
            return;
        }
    }

    s->v25();
    p = (u8 *) func_020800d0();
    func_0204f794(out, p[0], p[1] + 1);
    func_020e895c((char *) s + 0x5c, out[0], 0x400);
    func_020e895c((char *) s + 0x64, out[2], 0x400);

    if (func_020164a0((char *) s + 0x334, 0) == 0x3b) {
        mode = ((Sbits *) s)->mode;
        switch (mode) {
            case 8:
            case 0xc:
            case 0x16:
            case 0x1b:
            case 0x22:
                func_02013bb0((char *) s + 0x558, s);
                break;
            default:
                break;
        }
    }
}
