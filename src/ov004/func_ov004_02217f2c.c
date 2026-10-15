/* func_ov004_02217f2c @ 0x02217f2c, 0x1a8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int x, y;
} Cell;
#define H(p, o) (*(u16 *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern void *func_ov004_0223cb10(void), *func_ov004_0223ca9c(void *, void *);
extern u8 *func_020961a8(int);
extern int func_ov004_0223c700(void);
extern int func_ov004_0223cb20(void *);
extern int func_020ea990(Vec *, Vec *);
extern int func_ov004_022180d4(Cell *);
extern int func_ov004_0223cb18(void *);
extern int func_ov004_0220fe24(Vec *, int, int, int, int);
extern int func_ov004_0223cb30(void *);
extern int func_ov004_0222c14c(int *, int *, short *, short, int);
extern Cell *func_ov004_02218384(Cell *), *func_ov004_02218374(Cell *), *func_ov004_02218394(Cell *, int);
extern int func_ov004_022185b0(void *, Cell *);
extern void func_0204f794(Vec *, int, int);
extern void func_020ea6e0(Vec *, int);
extern Vec *func_ov004_0223cb28(void *);
void func_ov004_02217f2c(u8 *self)
{
    short angle;
    Cell chosen;
    Cell cells[2];
    Vec first, second, playerpos, offset, probe;
    int progress = 0;
    void *ride = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    u8 *player = func_020961a8(4);
    if (ride && player && func_ov004_0223c700() && (func_ov004_0223cb20(ride) == 2 || func_ov004_0223cb20(ride) == 0)) {
        Cell *cell;
        Vec *p;
        int d0, d1;
        func_ov004_02218384(cells);
        func_ov004_022185b0(self, cells);
        cell = func_ov004_02218394(cells, 0);
        func_0204f794(&first, cell->x, cell->y);
        cell = func_ov004_02218394(cells, 1);
        func_0204f794(&second, cell->x, cell->y);
        p = (Vec *) (player + 0x5c);
        playerpos.x = p->x;
        playerpos.y = p->y;
        playerpos.z = p->z;
        d0 = func_020ea990(&playerpos, &first);
        d1 = func_020ea990(&playerpos, &second);
        chosen.x = 0;
        chosen.y = 0;
        if (d0 < d1) {
            Cell *c = func_ov004_02218394(cells, 0);
            chosen.x = c->x;
            chosen.y = c->y;
        } else {
            Cell *c = func_ov004_02218394(cells, 1);
            chosen.x = c->x;
            chosen.y = c->y;
        }
        if (func_ov004_022180d4(&chosen)) {
            int z;
            offset.x = 0;
            offset.y = 0;
            offset.z = 0x2000;
            func_020ea6e0(&offset, func_ov004_0223cb18(ride));
            z = offset.z + func_ov004_0223cb28(ride)->z;
            probe.x = offset.x + func_ov004_0223cb28(ride)->x;
            probe.y = 0;
            probe.z = z;
            if (func_ov004_0220fe24(&probe, 0x800, 0x2000, 0x800, 0)) {
                if (H(self, 0x844) < 7) {
                    progress = 1;
                    H(self, 0x844)++;
                }
                if (func_ov004_0223cb30(ride) > 0x200 && H(self, 0x844) >= 7) {
                    Vec *pos;
                    angle = func_ov004_0223cb18(ride);
                    pos = func_ov004_0223cb28(ride);
                    func_ov004_0222c14c(&pos->x, &func_ov004_0223cb28(ride)->z, &angle, (short) (S(self, 0x8e) - 0x4000), 0);
                    H(self, 0x844) = 0;
                }
            }
        }
        func_ov004_02218374(cells);
    }
    if (!progress) {
        H(self, 0x844) = 0;
    }
}
