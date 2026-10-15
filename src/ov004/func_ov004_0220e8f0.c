/* func_ov004_0220e8f0 @ 0x0220e8f0, 0x2e4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int x, z;
} Pair;
typedef struct {
    int data[9];
} Points;
#define BYTE(p, o) (*(u8 *) ((char *) (p) + (o)))
#define VEC(p, o) ((Vec *) ((char *) (p) + (o)))
extern void *data_021c80bc;
extern int func_020b67d4(void), func_ov004_0220fed0(void);
extern char *func_020961a8(int);
extern int func_ov004_0220d6b8(void *, char *);
extern void func_0204f818(int *, int *, Vec *);
extern void VEC_Add(Vec *, const Vec *, Vec *);
extern void *func_ov004_0223cd50(void);
extern char *func_ov004_0223cc10(void *, int, int, int);
extern void func_ov004_0220f100(char *, unsigned char, int);
extern void *func_ov004_0220db94(Points *);
extern void func_ov004_0220f27c(char *, Points *, Vec *, int);
extern Pair *func_ov004_0220db5c(Points *, unsigned);
extern u16 *func_0204f5e0(void *, int, int, int, int, u8);
extern void func_ov004_0220ef14(char *, int, int, int, int);
extern void func_ov004_0220db90(Points *);
extern u8 func_02031b38(int, int);
extern int func_ov004_0220ce2c(int objectword), func_02030890(Vec *), func_ov004_0223c5a4(Vec *);
extern unsigned func_ov004_0220db68(Points *);
static inline void copyvec(Vec *dst, const Vec *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}
#define CLEANUP()                                                                                                             \
    do {                                                                                                                      \
        func_ov004_0220ef14(self, 0, 0, 0, 0);                                                                                \
        func_ov004_0220db90(&half);                                                                                           \
        func_ov004_0220db90(&full);                                                                                           \
    } while (0)
int func_ov004_0220e8f0(char *self, Vec *offset, int extent)
{
    char *occupied;
    char *condition_object;
    int x, z, hz;
    void *grid;
    u16 *tile, *other;
    int hx, qx, qz;
    char *player;
    Vec *source;
    unsigned i;
    int sx, sz, dx, dz;
    Vec original, destination;
    Points full, half;
    if (BYTE(self, 0x77d)) {
        return 0;
    }
    if (!func_020b67d4()) {
        return 0;
    }
    if (!func_ov004_0220fed0()) {
        return 0;
    }
    grid = data_021c80bc;
    player = func_020961a8(4);
    if (BYTE(self, 0x288) == 1) {
        return 0;
    }
    if (!grid || !player) {
        return 0;
    }
    if (!func_ov004_0220d6b8(self + 0x18c, self)) {
        return 0;
    }
    source = VEC(player, 0x5c);
    original.x = source->x;
    original.y = source->y;
    original.z = source->z;
    func_0204f818(&sx, &sz, &original);
    copyvec(&destination, &original);
    if (offset) {
        VEC_Add(&destination, offset, &destination);
    }
    func_0204f818(&dx, &dz, &destination);
    occupied = func_ov004_0223cc10(func_ov004_0223cd50(), dx, dz, 0);
    func_ov004_0220f100(self, 0, 0);
    func_ov004_0220db94(&full);
    func_ov004_0220f27c(self, &full, offset, extent);
    func_ov004_0220db94(&half);
    func_ov004_0220f27c(self, &half, offset, extent >> 1);
    for (i = 0; i < func_ov004_0220db68(&full); i++) {
        x = func_ov004_0220db5c(&full, i)->x;
        z = func_ov004_0220db5c(&full, i)->z;
        qx = x >> 4;
        qz = z >> 4;
        tile = func_0204f5e0(grid, qx, qz, x - (qx << 4), z - (qz << 4), 0);
        if (!offset && sx == x && sz == z) {
            CLEANUP();
            return 0;
        }
        if (!offset) {
            hz = func_ov004_0220db5c(&half, i)->z;
            hx = func_ov004_0220db5c(&half, i)->x;
            qx = hx >> 4;
            qz = hz >> 4;
            other = func_0204f5e0(grid, qx, qz, hx - (qx << 4), hz - (qz << 4), 0);
            if (other && *other != 0xfff1) {
                CLEANUP();
                return 0;
            }
        }
        if (tile && *tile != 0xfff1) {
            CLEANUP();
            return 0;
        }
        if (!func_02031b38(x, z)) {
            CLEANUP();
            return 0;
        }
        if ((condition_object = func_ov004_0223cc10(func_ov004_0223cd50(), x, z, 1)) != 0 &&
            func_ov004_0220ce2c((int) condition_object)) {
            CLEANUP();
            return 0;
        }
        if (extent == 0) {
            if ((occupied && !BYTE(occupied, 0x78c) && occupied != self) || func_02030890(&destination) != -1 ||
                func_ov004_0223c5a4(&destination)) {
                CLEANUP();
                return 0;
            }
        }
    }
    CLEANUP();
    return 1;
}
