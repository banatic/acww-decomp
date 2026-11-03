/* room_villager_3: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221ea40 @ 0x0221ea40, 0x58 bytes, Thumb
 * func_ov004_0221e8f0 @ 0x0221e8f0, 0x150 bytes, Thumb
 * func_ov004_0221e8b8 @ 0x0221e8b8, 0x38 bytes, Thumb
 * func_ov004_0221e880 @ 0x0221e880, 0x38 bytes, Thumb
 * func_ov004_0221e87c @ 0x0221e87c, 0x2 bytes, Thumb
 */

#include "types.h"

extern int data_ov004_0225395c[2];
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern u16 data_020c80f8;
extern int func_02019de8(void *);
extern int func_02019e00(void *);
extern int func_020644cc(int);
extern int func_ov004_0221ea98(void *, int *, int *, void *);
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *argument0);
extern void func_0201cc48(void *argument0);
extern int func_0203e020(int argument0);

int func_ov004_0221ea40(char *a, char *b)
{
    struct UnkStruct_0221ea40 {
        int a, b;
    };
    *(struct UnkStruct_0221ea40 *) (b + 0x898) = *(struct UnkStruct_0221ea40 *) &data_ov004_0225395c[0];
    func_02019d0c(b + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    *(int *) (a + 0x10) = 0;
    return 1;
}

int func_ov004_0221e8f0(char *self, char *actor)
{
    void *queue = actor + 0x564;
    int x, y;
    short angle;
    if (func_02019de8(queue)) {
        x = 0;
        y = 0;
        if (func_020644cc(7) == 0) {
            if (*(short *) (actor + 0x8e) & 0x3fff) {
                angle = func_020644cc(4) << 14;
                if (angle == *(short *) (actor + 0x8e)) {
                    angle += 0x4000;
                }
                func_02019d0c(queue, 3, 1, 0, 0, 0, (short) angle, 0, 0, (unsigned short) ((*(unsigned short *) &data_020c80f8)), 0);
            } else if (func_020644cc(3) != 0 && func_ov004_0221ea98(self, &x, &y, actor)) {
                func_02019d0c(queue, 1, 1, x, y, 0, 0, 0, 0, (unsigned short) ((*(unsigned short *) &data_020c80f8)), 0);
                *(int *) (self + 0x10) = 60;
            } else {
                angle = func_020644cc(4) << 14;
                if (angle == *(short *) (actor + 0x8e)) {
                    angle += 0x4000;
                }
                func_02019d0c(queue, 3, 1, 0, 0, 0, (short) angle, 0, 0, (unsigned short) ((*(unsigned short *) &data_020c80f8)), 0);
            }
        } else {
            func_02019d0c(queue, 0, 1, 0, 0, 0, 0, 0, 0, (unsigned short) ((*(unsigned short *) &data_020c80f8)), 0);
        }
    } else if (*(int *) (self + 0x10) == 0 && func_02019e00(queue) == 1) {
        func_02019d0c(queue, 0, 1, 0, 0, 0, 0, 0, 0, (unsigned short) ((*(unsigned short *) &data_020c80f8)), 0);
    }
    return 0;
}

int func_ov004_0221e8b8(int a0, void *self)
{
    int r1 = func_02016104((char *) self + 0x680);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov004_0221e880(char *self, char *a1)
{
    // DECLS
    int v1;
    // ENDDECLS
    v1 = func_02014868((void *) ((void *) (a1 + 0x618)));
    if (v1 == 0x0) {
        func_0201cc48(a1 + 0x83c);
        func_0203e020((int) (a1));
        *(u8 *) (self + 0xc) = 0x1;
        return 0x1;
    }
    return v1;
}

void func_ov004_0221e87c(void) {}
