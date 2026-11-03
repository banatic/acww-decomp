/* room_villager: 8 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221e718 @ 0x0221e718, 0x4 bytes, Thumb
 * func_ov004_0221e634 @ 0x0221e634, 0xe4 bytes, Thumb
 * func_ov004_0221e630 @ 0x0221e630, 0x4 bytes, Thumb
 * func_ov004_0221e5c0 @ 0x0221e5c0, 0x70 bytes, Thumb
 * func_ov004_0221e594 @ 0x0221e594, 0x2c bytes, Thumb
 * func_ov004_0221e374 @ 0x0221e374, 0x220 bytes, Thumb
 * func_ov004_0221e33c @ 0x0221e33c, 0x38 bytes, Thumb
 * func_ov004_0221e308 @ 0x0221e308, 0x34 bytes, Thumb
 */

#include "types.h"

#define OWNER (*(int *) (data_020ccf94 + 0x64))
#define STATE (*(int *) (self + 0x8d8))

extern int func_0201c0e0(char *self);
extern int func_0201c040(char *self, int *p, int *q);
extern void func_0201c054(char *self, int a, int b, int c);
extern int func_0207f150(int h);
extern void func_0202dc3c(char *a, char *b, int c);
extern int func_0201c2a4(char *self, int n);
extern void func_02016108(char *a, int b);
extern void func_ov004_0221eb6c(char *a, char *b, int c);
extern int func_ov004_0221eb44(char *a, char *b);
extern int func_020a7278(void);
extern char *data_020ccf94;
extern int func_02014868(void *);
extern int func_0201c014(void *);
extern int func_0201cddc(char *);
extern void *func_0202e5e0(void *);
extern void func_02084f84(void *object);
extern void func_020edf54(void *);
extern void func_ov004_0221ebf4(void *);
extern void *data_ov004_022539cc;

int func_ov004_0221e718(void)
{
    return 1;
}

int func_ov004_0221e634(int unused, char *self)
{
    // DECLS
    int p, q;
    int h;
    // ENDDECLS

    if (func_0201c0e0(self) != 0) {
        p = 4;
        q = 4;
        h = *(int *) (self + 0x830);
        if (func_0201c040(self, &p, &q) != 0 && p == *(int *) (data_020ccf94 + 0x64) && p == q) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
            if (h != 0 && func_0207f150(h) != 3) {
                *(int *) (self + 0x8d8) = 0xc;
            } else {
                *(int *) (self + 0x8d8) = 0;
            }
            func_0202dc3c(self + 0x680, self, *(int *) (self + 0x8d8));
            func_02016108(self + 0x680, func_0201c2a4(self, 4));
            func_ov004_0221eb6c(self + 0x8a0, self, 1);
        } else if (func_020a7278() != 0 && q == 4) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
            if (func_ov004_0221eb44(self + 0x8a0, self) == 0) {
                func_ov004_0221eb6c(self + 0x8a0, self, 0);
            }
        }
    }
    return 0;
}

int func_ov004_0221e630(void)
{
    return 1;
}

int func_ov004_0221e5c0(void *unused, char *o)
{
    int x;
    int y;
    if (func_0201c0e0((char *) o) != 0) {
        x = 4;
        y = 4;
        if (func_0201c040((char *) o, &x, &y) != 0) {
            if (x == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054((char *) o, 1, *(int *) (data_020ccf94 + 0x64), 4);
                    if (func_ov004_0221eb44((char *) (o + 0x8a0), (char *) o) == 0) {
                        func_ov004_0221eb6c((char *) (o + 0x8a0), (char *) o, 0);
                    }
                }
            }
        }
    }
    return 0;
}

int func_ov004_0221e594(void *p)
{
    if (func_02014868((char *) p + 0x618) != 0) {
        goto ret0;
    }
    if (func_0201c014(p) == 0) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}

void func_ov004_0221e374(char *self, int event, int player)
{
    switch (event) {
        case 3:
            *(u8 *) (self + 0x560) = player;
            if (player != 4) {
                func_0201c054(self, 1, OWNER, player);
                func_ov004_0221eb6c(self + 0x8a0, self, 2);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, OWNER, OWNER);
                if (*(void **) (self + 0x830) && func_0207f150((int) (*(void **) (self + 0x830))) != 3) {
                    STATE = 12;
                } else {
                    switch (func_0201cddc(self)) {
                        case 1:
                            STATE = 3;
                            break;
                        case 0:
                            STATE = 5;
                            break;
                        case 8:
                        case 9:
                            STATE = 11;
                            break;
                        default:
                            STATE = 0;
                            break;
                    }
                }
                func_ov004_0221eb6c(self + 0x8a0, self, 2);
            }
            break;
        case 0:
            *(u8 *) (self + 0x560) = player;
            if (player != 4 && player != OWNER) {
                func_0201c054(self, 1, player, player);
                func_ov004_0221eb6c(self + 0x8a0, self, 4);
            } else if (func_0201c0e0(self)) {
                func_0201c054(self, 1, OWNER, OWNER);
                func_0202dc3c(self + 0x680, self, STATE);
                func_02016108(self + 0x680, func_0201c2a4(self, 4));
                func_ov004_0221eb6c(self + 0x8a0, self, 1);
                STATE = 0;
            }
            break;
        case 8:
            if (player == 4) {
                if (func_020a7278()) {
                    func_0201c054(self, 1, OWNER, 4);
                    if (!func_ov004_0221eb44(self + 0x8a0, self)) {
                        func_ov004_0221eb6c(self + 0x8a0, self, 0);
                    }
                } else {
                    func_0201c054(self, 1, 4, OWNER);
                    func_ov004_0221eb6c(self + 0x8a0, self, 3);
                }
            }
            break;
        case 4:
            if (func_0201c014((void *) self) && func_0201c0e0(self)) {
                int a = 4, b = 4;
                if (func_0201c040(self, &a, &b)) {
                    if ((player != 4 && player == b) || player == 4) {
                        func_0201c054(self, 1, OWNER, 4);
                        if (!func_ov004_0221eb44(self + 0x8a0, self)) {
                            func_ov004_0221eb6c(self + 0x8a0, self, 0);
                        }
                    }
                }
            }
            break;
    }
}

void *func_ov004_0221e33c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022539cc;
    func_02084f84(self + 0x8b4);
    func_ov004_0221ebf4(self + 0x8a0);
    func_0202e5e0(self);
    func_020edf54(self);
    return self;
}

void *func_ov004_0221e308(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022539cc;
    func_02084f84(self + 0x8b4);
    func_ov004_0221ebf4(self + 0x8a0);
    func_0202e5e0(self);
    return self;
}
