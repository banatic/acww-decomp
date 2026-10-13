/* func_ov004_0223b574 @ 0x0223b574, 0x284 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec {
    int x, y, z;
};
struct Footprint;
extern "C" {
int func_0204bcdc(u16 *);
int func_0204bc64(u16 *);
void *func_ov004_0223ce84(void);
int func_ov004_0223cda4(void *);
int func_ov004_02211394(int, int, int, int, u8, int);
int func_020b67d4(void);
int func_02053be0(int);
int func_ov004_0220f240(int);
void func_0204f818(int *, int *, Vec *);
int func_ov004_0223b958(int *, int *, Vec *, int, u32);
void func_0204f794(Vec *, int, int);
int func_ov004_0223b7f8(int *, int, int, int, int, u8, int, int);
u16 func_0204bc50(int, int);
void func_02052e3c(Footprint *, u16 *);
void func_02052e38(Footprint *);
u8 func_02052e20(Footprint *);
short *func_02052dc0(Footprint *, u32);
void VEC_Add(Vec *, Vec *, Vec *);
void func_020eab08(Vec *, int);
void func_020eaca0(Vec *, Vec *, Vec *);
short func_020e8ed8(int, int);
int func_020e8b4c(int, int);
extern u8 data_ov004_02247cdc[];
}
struct Coord {
    short x, z;
    Coord(short a, short b) : x(a), z(b) {}
};
struct Footprint {
    int kind, direction;
    Footprint(u16 *item)
    {
        func_02052e3c(this, item);
    }
    ~Footprint()
    {
        func_02052e38(this);
    }
};
extern "C" int func_ov004_0223b574(int *out, u16 *item, Vec *position, int angle, int mode)
{
    u32 limit;
    int index, size, base;

    u16 variant;
    int originalX, originalZ, nearX, nearZ;
    Vec nearPosition;
    if (!func_0204bcdc(item)) {
        return 0;
    }
    if (!func_ov004_0223cda4(func_ov004_0223ce84())) {
        return 1;
    }
    if (mode == 2) {
        *out = func_ov004_02211394(0, 0, func_0204bc64(item), 0, 0, 2);
        return 3;
    }
    if (!func_020b67d4()) {
        return 0;
    }
    index = func_0204bc64(item);
    size = func_02053be0(index);
    base = func_ov004_0220f240((short) (angle + 0x8000));
    func_0204f818(&originalX, &originalZ, position);
    // ROM guard 022595d4; four 4-byte coordinate pairs at 02259688.
    static Coord offsets[4] = {Coord(0, 0), Coord(-1, 0), Coord(0, -1), Coord(-1, -1)};
    for (int pass = 1; pass >= 0; --pass) {
        for (u32 side = 0; side < 4; ++side) {
            if (func_ov004_0223b958(&nearX, &nearZ, position, angle, side)) {
                func_0204f794(&nearPosition, nearX, nearZ);
                for (short rotation = 0; rotation < 4; ++rotation) {
                    int facing = (base + data_ov004_02247cdc[rotation]) & 3;
                    if (size == 2) {
                        limit = 4;
                    } else {
                        limit = 1;
                    }
                    for (u32 candidate = 0; candidate < limit; ++candidate) {
                        int x = nearX + offsets[candidate].x;
                        int z = nearZ + offsets[candidate].z;
                        if (func_ov004_0223b7f8(out, x, z, facing, index, (u8) pass, originalX, originalZ) == 3) {
                            if (size == 1) {
                                variant = func_0204bc50(index, facing);
                                int direction = (short) (facing << 14);
                                Footprint footprint(&variant);
                                Vec sum;
                                sum.x = 0;
                                sum.y = 0;
                                sum.z = 0;
                                Vec point, delta;
                                u32 count = func_02052e20(&footprint);
                                for (u32 i = 0; i < count; ++i) {
                                    int tx = x + func_02052dc0(&footprint, i)[0];
                                    int tz = z + func_02052dc0(&footprint, i)[1];
                                    func_0204f794(&point, tx, tz);
                                    VEC_Add(&sum, &point, &sum);
                                }
                                func_020eab08(&sum, count << 12);
                                func_020eaca0(&delta, position, &sum);
                                if (func_020e8b4c(direction, func_020e8ed8(delta.x, delta.z)) > 0x4000) {
                                    short *first = func_02052dc0(&footprint, 1);
                                    short *second = func_02052dc0(&footprint, 1);
                                    if (func_ov004_0223b7f8(out, x + first[0], z + second[1], (facing + 2) & 3, index,
                                                            (u8) pass, originalX, originalZ) == 3) {
                                        return 3;
                                    }
                                }
                            }
                            return 3;
                        }
                    }
                }
            }
        }
    }
    return 2;
}
