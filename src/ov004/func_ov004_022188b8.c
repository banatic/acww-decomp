/* func_ov004_022188b8 @ 0x022188b8, 0x1a4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int x, y;
} Cell;
typedef struct {
    unsigned count;
    Cell cells[4];
} List;
#define W(p, o) (*(int *) ((p) + (o)))
#define H(p, o) (*(u16 *) ((p) + (o)))
extern void func_ov004_0220cfec(void *, int), func_0204f818(int *, int *, Vec *), func_ov004_0220db90(List *),
    func_ov004_02218848(void *, Vec *, void *);
extern List *func_ov004_0220db94(List *);
extern void func_ov004_0220f27c(void *, List *, int, int);
extern int func_ov004_0220ffbc(void *);
extern int func_ov004_022107d4(void *);
extern int func_ov004_0222c268(Vec *, unsigned), func_ov004_0223c700(void), func_ov004_0223cb20(void *),
    func_ov004_0220fe24(Vec *, int, int, int, int), func_ov004_0223cb30(void *),
    func_ov004_0222c0b8(int *, int *, short *, u8 *);
extern unsigned func_ov004_0220db68(List *);
extern Cell *func_ov004_0220db5c(List *, unsigned);
extern void *func_ov004_0223cb10(void), *func_ov004_0223ca9c(void *, void *);
int func_ov004_022188b8(u8 *self)
{
    u8 action;
    int x, y;
    Vec pos;
    List list;
    Vec probe;
    int progress;
    void *ride;
    if (W(self, 0x780) == 0x2c) {
        unsigned i;
        func_ov004_0220cfec(self + 0x764, 0);
        for (i = 0; i < 4; i++) {
            if (func_ov004_0222c268(&pos, i)) {
                unsigned j;
                func_0204f818(&x, &y, &pos);
                func_ov004_0220db94(&list);
                func_ov004_0220f27c(self, &list, 0, 0);
                for (j = 0; j < func_ov004_0220db68(&list); j++) {
                    if (x == func_ov004_0220db5c(&list, j)->x && y == func_ov004_0220db5c(&list, j)->y) {
                        func_ov004_0220cfec(self + 0x764, 1);
                        func_ov004_0220ffbc(self);
                        func_ov004_022107d4(self);
                        break;
                    }
                }
                func_ov004_0220db90(&list);
            }
        }
    } else if (W(self, 0x780) == 9) {
        func_ov004_0220ffbc(self);
        func_ov004_022107d4(self);
    }
    progress = 0;
    ride = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    if (ride && func_ov004_0223c700()) {
        int eligible = 0;
        action = 0;
        if (W(self, 0x780) != 0x26) {
            if (func_ov004_0223cb20(ride) == 0) {
                eligible = 1;
                action = 0;
            }
        } else {
            if (func_ov004_0223cb20(ride) == 0) {
                eligible = 1;
                action = 0;
            } else if (func_ov004_0223cb20(ride) == 3) {
                eligible = 1;
                action = 1;
            } else if (func_ov004_0223cb20(ride) == 1) {
                eligible = 1;
                action = 2;
            }
        }
        if (eligible) {
            func_ov004_02218848(self, &probe, ride);
            if (func_ov004_0220fe24(&probe, 0x800, 0x2000, 0x800, 0)) {
                if (H(self, 0x844) < 7) {
                    progress = 1;
                    H(self, 0x844)++;
                }
                if (func_ov004_0223cb30(ride) > 0x200 && H(self, 0x844) >= 7) {
                    func_ov004_0222c0b8(&probe.x, &probe.z, (short *) (self + 0x8e), &action);
                    H(self, 0x844) = 0;
                }
            }
        }
    }
    if (!progress) {
        H(self, 0x844) = 0;
    }
    return 1;
}
