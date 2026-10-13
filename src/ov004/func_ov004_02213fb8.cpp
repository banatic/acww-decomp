/* func_ov004_02213fb8 @ 0x02213fb8, 0xb8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_02213fb8 {
  public:
    virtual void v00() = 0;
    virtual void v01() = 0;
    virtual void v02() = 0;
    virtual void v03() = 0;
    virtual void v04() = 0;
    virtual void v05() = 0;
    virtual void v06() = 0;
    virtual void v07() = 0;
    virtual void v08() = 0;
    virtual void v09() = 0;
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
    virtual void v26() = 0;
    virtual void v27() = 0;
    virtual void v28(int, int) = 0;
};

extern "C" {
void *func_ov004_0220fde0(void *self);
int func_0204bc50(void *p, int a);
void func_02061e2c(u16 *a, u16 *b);
void func_ov004_0220ffa4(void *self);
void *func_0209d324(void);
int func_020e9948(void *a, int n);
void func_0203d064(int a, u16 *b, int c);
int func_ov004_0220d2b8(void *p);
}

extern "C" int func_ov004_02213fb8(UnkStruct_02213fb8 *selfp)
{
    char *self = (char *) selfp;
    volatile u16 vv[2];
    u16 t;
    int m;

    *(u8 *) (self + 0x873) = 1;
    vv[0] = (u16) func_0204bc50(func_ov004_0220fde0(self), 0);
    m = 0;
    t = vv[0];
    if (t >= 0x3984 && t <= 0x3d83) {
        m = 1;
    }
    if (m != 0) {
        func_02061e2c((u16 *) &vv[1], (u16 *) &vv[0]);
        func_ov004_0220ffa4(self);
        *(int *) (self + 0x844) = func_020e9948(func_0209d324(), 0x2c4);
        func_0203d064(*(int *) (self + 0x844), (u16 *) &vv[1], 0);
        if (func_ov004_0220d2b8(self + 0x740) != 0) {
            selfp->v28(0, 0xff);
        } else {
            selfp->v28(1, 0xff);
        }
    }
    selfp->v28(0, 0xff);
    *(u8 *) (self + 0x873) = 0;
    return 1;
}
