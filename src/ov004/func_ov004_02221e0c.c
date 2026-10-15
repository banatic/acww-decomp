/* func_ov004_02221e0c @ 0x02221e0c, 0x28c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
#define B(p, o) (*(u8 *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
#define W(p, o) (*(int *) ((p) + (o)))
#define V(p, o) ((Vec *) ((p) + (o)))
extern unsigned int data_021fbdd0;
extern u16 data_020c80f8;
extern int func_02019e00(void *);
extern void func_0201ca40(void *, char *);
extern int func_ov004_02222178(char *, int);
extern int func_ov004_0221e1e0(Vec *, Vec *, int);
extern int func_02019d0c(void *, int, int, int, int, short, short, int, int, u16, u16);
extern int func_020644cc(int);
extern int func_02019de8(void *);
extern int func_02019c6c(void *, int, u16);
extern int func_0201c194(char *, Vec *);
extern void func_0201b044(void *, Vec *);
extern int func_020eaa2c(Vec *, Vec *);
extern int func_020ea990(Vec *, Vec *);
static inline void copy(Vec *d, const Vec *s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}
void func_ov004_02221e0c(char *self)
{
    Vec next;
    if (B(self, 0x897) != 0 && func_02019e00(self + 0x564) == 1 && data_021fbdd0 % 14 == 0) {
        func_0201ca40(self + 0x83c, self);
    }
    if (B(self, 0x508) != 0 && func_02019e00(self + 0x564) == 1 && func_ov004_02222178(self, 1)) {
        return;
    }
    if (func_02019e00(self + 0x564) == 0) {
        if (H(self, 0xa76) != 0) {
            --H(self, 0xa76);
        }
        if (H(self, 0xa76) == 0) {
            H(self, 0xa74) = func_ov004_0221e1e0(V(self, 0xa84), V(self, 0x5c), S(self, 0x8e));
            copy(V(self, 0xa78), V(self, 0xa84));
            if (S(self, 0xa74) != S(self, 0x8e)) {
                if (func_02019d0c(self + 0x564, 3, 1, 0, 0, 0, S(self, 0xa74), 0, 0, data_020c80f8, 0)) {
                    if (B(self, 0x897) != 0) {
                        H(self, 0xa76) = func_020644cc(70) + 50;
                    } else {
                        H(self, 0xa76) = func_020644cc(70) + 20;
                    }
                }
            } else {
                if (func_02019d0c(self + 0x564, 1, 1, W(self, 0xa84), W(self, 0xa8c), 0, 0, 0, 0, data_020c80f8, 0)) {
                    if (B(self, 0x897) != 0) {
                        H(self, 0xa76) = func_020644cc(70) + 50;
                    } else {
                        H(self, 0xa76) = func_020644cc(80) + 20;
                    }
                }
            }
        } else {
            if (func_02019de8(self + 0x564)) {
                func_02019c6c(self + 0x564, 1, data_020c80f8);
            }
        }
    } else if (func_02019e00(self + 0x564) == 3) {
        if (func_02019de8(self + 0x564)) {
            func_02019d0c(self + 0x564, 1, 1, W(self, 0xa84), W(self, 0xa8c), 0, 0, 0, 0, data_020c80f8, 0);
        }
    } else if (func_02019e00(self + 0x564) == 1) {
        switch (func_0201c194(self, &next)) {
            case 1:
                func_02019c6c(self + 0x564, 1, data_020c80f8);
                break;
            case 2:
                copy(V(self, 0xa78), &next);
                func_0201b044(self + 0x350, V(self, 0xa78));
                break;
            default:
                if (func_020eaa2c(V(self, 0xa78), V(self, 0xa84))) {
                    copy(V(self, 0xa78), V(self, 0xa84));
                    func_0201b044(self + 0x350, V(self, 0xa84));
                } else if (func_020ea990(V(self, 0xa84), V(self, 0x5c)) < 0x200) {
                    func_ov004_02222178(self, 1);
                }
                break;
        }
    }
}
