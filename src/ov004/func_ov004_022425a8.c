/* func_ov004_022425a8 @ 0x022425a8, 0x278 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern char *func_ov004_0223ee38(void);
extern int func_0200322c(Vec *, Vec *);
extern int func_020ea990(Vec *, Vec *);
extern void func_ov004_02244fb8(Vec *, int);
extern int func_020644cc(int);
extern void func_020eac34(Vec *, Vec *, int);
extern void VEC_Add(Vec *, Vec *, Vec *);
extern void VEC_Subtract(Vec *, Vec *, Vec *);
extern void func_ov004_02242a9c(char *, int, int);
extern int func_ov004_02244c20(char *);
extern u8 data_ov004_02259a24;
void func_ov004_022425a8(char *self)
{
    char *peer;
    int angle, choice, distance;
    int steerPeer, steerSelf;
    short *timer;
    Vec a, b, c, d, e, f, g, h, i, j;
    Vec *position, *other;
    short *step;
    peer = func_ov004_0223ee38();
    position = (Vec *) (self + 0x2c8);
    other = (Vec *) (peer + 0x2c8);
    angle = func_0200322c(other, position);
    timer = (short *) (self + 0x168);
    choice = W(self, 0x4c);
    distance = func_020ea990(position, other);
    steerPeer = 1;
    steerSelf = 1;
    step = (short *) (self + 0x98);
    func_ov004_02244fb8(&a, angle);
    func_ov004_02244fb8(&b, func_0200322c(position, other));
    if (data_ov004_02259a24 % 15 == 0) {
        choice = func_020644cc(100);
        W(self, 0x4c) = choice;
        *step = func_020644cc(5) + 5;
        if (func_020644cc(100) > 50) {
            *step = -*step;
        }
    }
    if (*step > 0) {
        --*step;
    } else if (*step < 0) {
        ++*step;
    }
    if (choice < 30 && distance < 0xccd) {
        steerPeer = 0;
        if (*step <= 0) {
            func_020eac34(&c, &b, 0x2000);
            VEC_Add(position, &c, position);
        } else {
            func_020eac34(&d, &a, 0x2000);
            VEC_Subtract(other, &d, other);
        }
    } else if (choice < 60 && distance < 0xccd) {
        steerSelf = 0;
        if (*step <= 0) {
            func_020eac34(&e, &b, 0x2000);
            VEC_Subtract(position, &e, position);
        } else {
            func_020eac34(&f, &a, 0x2000);
            VEC_Add(other, &f, other);
        }
    } else if ((distance > 0x5800 || choice < 80) && distance > 0x99a) {
        if (*step <= 0) {
            func_020eac34(&g, &b, 0xa000);
            VEC_Add(position, &g, position);
        } else {
            func_020eac34(&h, &a, 0xa000);
            VEC_Add(other, &h, other);
        }
    } else if (distance < 0x5800) {
        if (choice < 90) {
            if (*step <= 0) {
                VEC_Subtract(position, &b, position);
            } else {
                VEC_Subtract(other, &a, other);
            }
        } else if (choice < 100) {
            if (*step <= 0) {
                func_020eac34(&i, &b, 0x5000);
                VEC_Subtract(position, &i, position);
            } else {
                func_020eac34(&j, &a, 0x5000);
                VEC_Subtract(other, &j, other);
            }
        }
    }
    if (steerSelf) {
        func_ov004_02242a9c(self, func_0200322c(position, other), *timer);
    } else {
        S(self, 0x192) = func_0200322c(position, other);
    }
    if (steerPeer) {
        func_ov004_02242a9c(peer, angle, *timer);
    } else {
        S(peer, 0x192) = func_0200322c(other, position);
    }
    ++*timer;
    if (func_ov004_02244c20(self)) {
        S(self, 0x172) = 25;
        *timer = 0;
    }
}
