/* func_ov004_022166b8 @ 0x022166b8, 0x168 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

class UnkStruct_022166b8 {
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
    virtual int v28(int, int) = 0;
};

extern "C" {
void func_ov004_0221041c(void *self, int a, int b, int c, int d);
int func_ov004_0220d2b8(void *p);
int func_ov004_0220d0a0(void *p, int a, int b);
int func_02052738(void *self, int a, int b, int c);
int func_ov004_0223c10c(void);
int func_020b6680(void);
int func_020b66b0(void);
int func_0207cec0(void *d, int a);
unsigned int func_0207f2c4(int result);
u16 *func_02060b70(void);
void func_02060afc(void);
}
extern int data_021e5a2c;
extern volatile u16 data_ov004_02256fec;

extern "C" int func_ov004_022166b8(UnkStruct_022166b8 *selfp)
{
    char *self = (char *) selfp;
    int s;
    int a;
    unsigned int n;
    int ok;
    u16 lo;
    u16 hi;
    volatile u16 t;
    int m;
    u16 lo2;
    u16 hi2;
    int idx;

    s = *(int *) (self + 0x780);
    if (s == 0x29 || s == 0x13) {
        func_ov004_0221041c(self, 0, 0, 0x1000, 0);
    }
    a = *(int *) (self + 0x594);
    func_ov004_0220d0a0(self + 0x848, a, func_ov004_0220d2b8(self + 0x740));
    if (*(int *) (self + 0x76c) == 1) {
        func_02052738(self, 0, 0xff, 1);
    } else if (func_ov004_0220d2b8(self + 0x740) != 0 && func_ov004_0223c10c() == 0) {
        if (func_020b6680() != 0) {
            n = 0;
            if ((m = func_0207cec0(&data_021e5a2c, func_020b66b0())) != 0) {
                n = func_0207f2c4(m);
            }
            ok = 0;
            lo = data_ov004_02256fec;
            hi = data_ov004_02256fec;
            if (hi >= 0x1323 && lo <= 0x1368) {
                ok = 1;
            }
            if (ok != 0) {
                selfp->v28(0, 0xff);
            } else if (selfp->v28(1, (u8) n) != 0) {
                data_ov004_02256fec = (n < 0x46) ? (u16) (n + 0x1323) : (u16) 0x1323;
            }
        } else {
            t = *func_02060b70();
            m = 0;
            lo2 = t;
            hi2 = t;
            if (hi2 >= 0x1323 && lo2 <= 0x1368) {
                m = 1;
            }
            if (m != 0) {
                idx = (lo2 >= 0x1323 && lo2 <= 0x1368) ? (lo2 - 0x1323) : -1;
                selfp->v28(1, (u8) idx);
            } else {
                func_02060afc();
                selfp->v28(0, 0xff);
            }
        }
    } else {
        selfp->v28(0, 0xff);
    }
    return 1;
}
