/* func_ov004_0223e618 @ 0x0223e618, 0x19c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
struct UnkStruct_0223e618 {
    int unk_00, unk_04, unk_08, w, h;
};
extern struct UnkStruct_0223e618 *data_021c80bc;
extern int func_0204ee7c(struct UnkStruct_0223e618 *, int, int);
extern u16 *func_0204f5e0(struct UnkStruct_0223e618 *, int, int, int, int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_020644cc(int);
extern void func_0204f794(Vec *, int, int);
extern void *func_02003348(int, int, Vec *, int, void *);
extern void *data_ov004_02259a18[];
extern u8 data_ov004_02259a08;
extern u8 data_ov004_02259a0c;

int func_ov004_0223e618(void *self)
{
    u8 count;
    struct UnkStruct_0223e618 *g;
    int x;
    int y;
    unsigned int *row;
    unsigned int rows[33];
    u8 slot;
    u8 pick;

    int yy;

    unsigned int bit;
    Vec pos;
    u16 *item;
    int hit;
    u16 tmp;
    int a;
    int bx, by;

    count = 0;
    g = data_021c80bc;
    for (y = 0; y < g->h; y++) {
        row = &rows[y];
        *row = 0;
        for (x = 0; x < g->w; x++) {
            if (g == 0) {
                continue;
            }
            if (func_0204ee7c(g, x, y) == 0) {
                continue;
            }
            bx = x >> 4;
            by = y >> 4;
            item = func_0204f5e0(g, bx, by, x - (bx << 4), y - (by << 4), 0);
            if (item == 0) {
                continue;
            }
            if (func_0204bcdc(item) != 0) {
                tmp = 0xfff1;
                a = func_0204bc64(item);
                hit = (a == func_0204bc64(&tmp));
            } else {
                hit = (*item == 0xfff1);
            }
            if (hit != 0) {
                count++;
                *row |= 1 << x;
            }
        }
    }
    for (slot = 0; slot < 3 && data_ov004_02259a08 < data_ov004_02259a0c; slot++) {
        if (count == 0) {
            break;
        }
        pos.x = 0;
        pos.y = 0;
        pos.z = 0;
        pick = func_020644cc(count--) + 1;
        for (yy = 0; yy < g->h; yy++) {
            int xx = 0;
            unsigned int *row2 = &rows[yy];
            int w = g->w;
            for (; xx < w; xx++) {
                bit = *row2;
                bit >>= xx;
                bit &= 1;
                if (bit != 0) {
                    pick--;
                }
                if (pick == 0) {
                    *row2 -= 1 << xx;
                    func_0204f794(&pos, xx, yy);
                    pos.y = 0x200;
                    yy = g->h;
                    break;
                }
            }
        }
        data_ov004_02259a18[slot] = func_02003348(0xc0, 0x1f, &pos, 0, self);
        data_ov004_02259a08++;
    }
    return 1;
}
