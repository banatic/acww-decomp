/* func_ov004_02241ba8 @ 0x02241ba8, 0x178 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int words[17];
} Probe;
#define W(p, o) (*(int *) ((p) + (o)))
#define S(p, o) (*(short *) ((p) + (o)))
extern int func_ov004_022430f8(void *), FX_MulFunc(int, int), func_020341c8(Probe *, int), func_020644cc(int);
extern void func_ov004_02244fb8(Vec *, int), func_02034270(Probe *, Vec *, int, int), func_0203423c(Probe *),
    func_ov004_02244be0(void *, int);
int func_ov004_02241ba8(u8 *self)
{
    Vec previous, direction;
    Probe probe;
    Vec *position = (Vec *) (self + 0x2c8);
    short *counter;
    int distance, result, angle, ticks, length, step;
    u8 kind;
    previous.x = position->x;
    previous.y = position->y;
    previous.z = position->z;
    counter = (short *) (self + 0x168);
    distance = 5;
    result = func_ov004_022430f8(self);
    kind = self[0x196];
    func_ov004_02244fb8(&direction, S(self, 0x192));
    if (kind == 30) {
        distance = 4;
    }
    if (result && kind != 52) {
        return result;
    }
    length = (distance + W(self, 0x16c)) << 12;
    position->x += FX_MulFunc(length, direction.x);
    position->z += FX_MulFunc(length, direction.z);
    if (kind == 52 || kind == 48) {
        int blocked;
        func_02034270(&probe, position, 0, 0);
        blocked = func_020341c8(&probe, 0) > 0x200;
        func_0203423c(&probe);
        if (blocked) {
            if (!result && kind == 52) {
                if (func_020644cc(100) < 50) {
                    S(self, 0x192) += 0x38e;
                } else {
                    S(self, 0x192) -= 0x38e;
                }
            }
            position->x = previous.x;
            position->y = previous.y;
            position->z = previous.z;
        }
    }
    if (kind == 55) {
        step = 0x71c;
    } else {
        step = 0xaaa;
    }
    ticks = *counter;
    if (ticks == 0) {
        angle = S(self, 0x192);
        S(self, 0x192) = angle + FX_MulFunc(step, 0x800);
    } else if (ticks % 4 == 0) {
        S(self, 0x192) = step + S(self, 0x192);
    } else if (ticks % 2 == 0) {
        S(self, 0x192) -= step;
    }
    (*counter)++;
    if ((u8) (kind + 0xca) <= 1) {
        func_ov004_02244be0(self, 0);
    }
    return result;
}
