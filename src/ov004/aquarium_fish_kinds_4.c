/* aquarium_fish_kinds_4: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022379ec @ 0x022379ec, 0x140 bytes, Thumb
 * func_ov004_022378ec @ 0x022378ec, 0x100 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec;

extern unsigned char *func_020961a8(int);
extern int func_0200322c(Vec *, Vec *);
extern int func_020e89dc(short *, int, int);
extern int func_ov004_02239bb4(Vec *, int, int);
extern int func_020e88dc(int *, int, int);
extern void func_ov004_02237870(void *);
extern long long func_020ea940(Vec *, Vec *);
extern Vec *func_02095794(int);
extern int func_ov004_022377ec(void *);
extern void func_ov004_02237794(void *);
extern void func_ov004_02237834(void *);

void func_ov004_022379ec(unsigned char *self)
{
    unsigned char *other = func_020961a8(4);
    if (!other) {
        self[0x255] = 0;
    } else {
        Vec position;
        long long distance;
        {
            Vec *p = (Vec *) (other + 0x5c);
            position.x = p->x;
            position.y = p->y;
            position.z = p->z;
        }
        func_020e89dc((short *) (self + 0x1c0), func_0200322c((Vec *) (self + 0x1a8), &position), 0x222);
        func_ov004_02239bb4((Vec *) (self + 0x1a8), *(int *) (self + 0x210), *(short *) (self + 0x1c0));
        if (*(int *) (other + 0x98)) {
            if (*(short *) (self + 0x1c4)) {
                func_020e89dc((short *) (self + 0x1c4), 0, 0x222);
            }
            if (*(int *) (self + 0x1ac) != 0x199a) {
                func_020e88dc((int *) (self + 0x1ac), 0x199a, *(int *) (self + 0x224));
            }
            self[0x259] = 0;
        } else {
            func_ov004_02237870(self);
            ++self[0x259];
            if (self[0x259] >= 70) {
                self[0x255] = 0;
                self[0x1ee] = 2;
                *(int *) (self + 0x158) = 0;
                self[0x259] = 0;
                return;
            }
        }
        distance = func_020ea940(&position, (Vec *) (self + 0x1a8));
        if (distance < 0x4000) {
            if (self[0x256]) {
                self[0x255] = 2;
                *(int *) (self + 0x158) = 0;
            }
        } else if (distance > 0x10000) {
            self[0x255] = 0;
            *(int *) (self + 0x158) = 0;
        }
        *(int *) (self + 0x110) = 0x1000;
    }
}

void func_ov004_022378ec(unsigned char *self)
{
    Vec *other = func_02095794(4);
    if (!other) {
        self[0x255] = 0;
    } else {
        long long distance;
        if (*(short *) (self + 0x1c4) != 0) {
            func_020e89dc((short *) (self + 0x1c4), 0, 0x16c);
        }
        if (*(int *) (self + 0x1ac) != 0x199a) {
            func_020e88dc((int *) (self + 0x1ac), 0x199a, *(int *) (self + 0x224));
        }
        switch (self[0x257]) {
            case 1:
                func_ov004_022377ec(self);
                break;
            case 2:
                func_ov004_02237794(self);
                break;
            case 0:
                func_ov004_02237834(self);
                break;
        }
        func_020e89dc((short *) (self + 0x1c0), func_0200322c((Vec *) (self + 0x1a8), other), 0x222);
        distance = func_020ea940(other, (Vec *) (self + 0x1a8));
        if (distance > 0x10000) {
            self[0x255] = 0;
            *(int *) (self + 0x158) = 0;
        } else if (distance > 0x4000) {
            self[0x255] = 1;
            *(int *) (self + 0x158) = 0;
        }
        *(int *) (self + 0x110) = 0x1000;
    }
}
