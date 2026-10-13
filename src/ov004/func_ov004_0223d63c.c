/* func_ov004_0223d63c @ 0x0223d63c, 0x1f0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    short x, y, z;
} Rot;
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define B(p, o) (*(signed char *) ((p) + (o)))
extern u8 *data_ov004_02259a14;
extern signed char data_ov004_02259a04;
extern void func_ov004_0223d9c4(void *, int, int), func_ov004_0223dc68(void *, int);
extern int func_ov004_0223db08(void *);
extern u8 *func_020961a8(int);
extern int func_020ea990(Vec *, Vec *);
extern short func_0200322c(Vec *, Vec *);
extern int FX_MulFunc(int, int);
extern void func_020550e4(void *, int), func_02055124(void *);
int func_ov004_0223d63c(u8 *self)
{
    short heading = S(self, 0x8e);
    Vec *position = (Vec *) (self + 0x5c);
    int found = 0;
    u8 i;
    func_ov004_0223d9c4(self, 60, 0xe38);
    self[0x260] = func_ov004_0223db08(self);
    for (i = 0; i < 2; i++) {
        u8 *other;
        if (i == 0) {
            other = func_020961a8(4);
        } else {
            other = data_ov004_02259a14;
        }
        if (other && !found) {
            Vec *otherpos = (Vec *) (other + 0x5c);
            if (func_020ea990(position, otherpos) < 0x1800) {
                short angle = func_0200322c(position, otherpos);
                if ((angle >= 0 && heading >= 0) || (angle <= 0 && heading <= 0)) {
                    int diff = angle - heading;
                    if (diff < 0) {
                        diff = -diff;
                    }
                    if (diff < 0x2aaa) {
                        ++S(self, 0x22e);
                        self[0x22a] = 1;
                        found = 1;
                        W(self, 0x98) = W(self, 0xd8);
                        func_ov004_0223dc68(self, 1);
                    }
                }
            }
        }
    }
    if (S(self, 0x22e) > 0) {
        int t = S(self, 0x22e) << 12;
        position->y = FX_MulFunc(0x99a - FX_MulFunc(0xcd, t), t);
        if (position->y < 3) {
            position->y = 3;
            S(self, 0x22e) = 0;
            self[0x22a] = 0;
            func_020550e4(self + 0x120, 0);
        } else {
            ++S(self, 0x22e);
            func_02055124(self + 0x120);
        }
    } else {
        if (B(self, 0x260) > 0) {
            if (B(self, 0x260) == 3) {
                if (self[0x262] == 1 || self[0x262] == 10) {
                    heading -= 0xaaa;
                } else {
                    heading += 0xaaa;
                }
            } else if (B(self, 0x260) == 1 || self[0x262] == 1) {
                heading -= 0xaaa;
                self[0x262] = 1;
            } else if (B(self, 0x260) == 2 || self[0x262] == 2) {
                heading += 0xaaa;
                self[0x262] = 2;
            }
        } else {
            if (data_ov004_02259a04 == 4) {
                heading += 0xaaa;
                data_ov004_02259a04 = -1;
            } else if (data_ov004_02259a04 == 2) {
                heading -= 0xaaa;
            }
            ++data_ov004_02259a04;
            if (self[0x262] < 10) {
                self[0x262] *= 10;
            }
        }
        func_ov004_0223dc68(self, 0);
    }
    {
        Rot *rotation = (Rot *) (self + 0x92);
        rotation->y = heading;
        S(self, 0x8e) = rotation->y;
    }
    return 1;
}
