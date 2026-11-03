/* music_player_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02216680 @ 0x02216680, 0x12 bytes, Thumb
 * func_ov004_02216630 @ 0x02216630, 0x50 bytes, Thumb
 * func_ov004_022165dc @ 0x022165dc, 0x54 bytes, Thumb
 * func_ov004_02216598 @ 0x02216598, 0x44 bytes, Thumb
 * func_ov004_02216558 @ 0x02216558, 0x3e bytes, Thumb
 */

#include "types.h"

typedef struct UnkStruct_02216680 UnkStruct_02216680;

struct UnkStruct_02216680 {
    void (**vt)(UnkStruct_02216680 *);
};

extern int func_ov004_0220cdf8(void *self);
extern volatile u16 data_ov004_02256fec;
extern void func_020356c4(int a, u16 b, int c, int d);
extern void *func_02060b34(u16 *p);
extern void func_02035638(u16 a);
extern int func_020b67d4(void);
extern int func_ov004_0220fed0(void);
extern int func_ov004_022164a0(void *self, int k);

void func_ov004_02216598(char *self, unsigned k, int c);

void func_ov004_02216680(UnkStruct_02216680 *self)
{
    self->vt[32](self);
}

int func_ov004_02216630(char *self)
{
    int ok;
    u16 lo, hi;

    func_ov004_02216598((char *) self, *(u8 *) (self + 0x845), func_ov004_0220cdf8(self));
    ok = 0;
    lo = data_ov004_02256fec;
    hi = data_ov004_02256fec;
    if (hi >= 0x1323 && lo <= 0x1368) {
        ok = 1;
    }
    if (ok) {
        data_ov004_02256fec = 0xfff1;
    }
    return 1;
}

void func_ov004_022165dc(char *self, unsigned k)
{
    u16 t;

    if (*(u8 *) (self + 0x844) == 0 && k < 0x46) {
        func_020356c4(0x11, (u16) (k + 0xb0), 0x7f, 0);
        t = k < 0x46 ? (u16) (0x1323 + k) : 0x1323;
        func_02060b34(&t);
        *(u8 *) (self + 0x844) = 1;
    }
}

void func_ov004_02216598(char *self, unsigned k, int c)
{
    u16 t;

    if (*(u8 *) (self + 0x844) != 0 && k < 0x46) {
        func_02035638((u16) (k + 0xb0));
        if (c != 0) {
            t = 0xfff1;
            func_02060b34(&t);
        }
        *(u8 *) (self + 0x844) = 0;
    }
}

void func_ov004_02216558(void *self, int k)
{
    switch (k) {
        case 1:
            if (func_020b67d4() != 0 && func_ov004_0220fed0() != 0) {
                func_ov004_022164a0(self, 1);
            } else {
                func_ov004_022164a0(self, 3);
            }
            break;
        case 8:
            func_ov004_022164a0(self, 0);
            break;
    }
}
