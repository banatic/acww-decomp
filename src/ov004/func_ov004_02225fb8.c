/* func_ov004_02225fb8 @ 0x02225fb8, 0x2b4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
typedef struct {
    int x, z;
} Pair;
#define BYTE(p, o) (*(u8 *) ((p) + (o)))
#define WORD(p, o) (*(int *) ((p) + (o)))
#define VEC(p, o) ((Vec *) ((p) + (o)))
extern void *data_021c80bc;
extern int data_ov004_02247780, data_ov004_02254aec;
extern int func_020b67d4(void);
extern int func_ov004_0223bbc0(int *, int *, u16 *, u16 *);
extern int func_ov004_0223bb88(unsigned);
extern int func_0200bdbc(char *, Pair *, int, int, short);
extern int func_ov004_0222ac24(char *, Pair *, int, int, short);
extern void func_0200fa1c(Vec *, char *, Vec *, u16 *, int *);
extern int func_0201005c(char *, Vec *, int);
extern u16 *func_0204f5a8(void *, Vec *, u8);
extern int func_02099fe8(void);
extern int func_0204bd08(u16 *);
extern void func_0204f818(int *, int *, Vec *);
extern unsigned func_020b2300(void);
extern int func_0200ff28(char *, Vec *, int, int);
extern int func_0200fd04(char *, Vec *, int);
static inline void copyvec(Vec *out, const Vec *in)
{
    out->x = in->x;
    out->y = in->y;
    out->z = in->z;
}
int func_ov004_02225fb8(char *self, int action)
{
    int x = 0, z = 0, cx, cz;
    Pair p0, p1, p2, p3, p4, p5;
    Vec position, val, val2;
    int candidate;
    void *grid;
    u16 *tile;
    if (!func_020b67d4()) {
        goto fail;
    }
    if (WORD(self, 0x800)) {
        goto fail;
    }
    candidate = func_ov004_0223bbc0(&cx, &cz, (u16 *) (self + 0x820), (u16 *) (self + 0x822));
    if (candidate >= 0 && (candidate == BYTE(self, 0x16d) || WORD(self, 0x170) == 1)) {
        if (!func_ov004_0223bb88(candidate)) {
            p0.x = 0;
            p0.z = 0;
            func_0200bdbc(self, &p0, candidate, 6, -1);
        } else {
            p1.x = (u8) cx;
            p1.z = (u8) cz;
            func_ov004_0222ac24(self, &p1, candidate, 6, -1);
        }
        return 1;
    }
    grid = data_021c80bc;
    if (candidate == -2) {
        if (WORD(self, 0x170) == 1) {
            func_0200fa1c(&val, self, VEC(self, 0x5c), (u16 *) (self + 0x8e), &data_ov004_02247780);
            copyvec(&position, &val);
        } else {
            position.x = WORD(self, 0x158);
            position.y = WORD(self, 0x15c);
            position.z = WORD(self, 0x160);
            if (!func_0201005c(self, &position, 14)) {
                goto fallback;
            }
        }
        tile = func_0204f5a8(grid, &position, 1);
        if (func_02099fe8() == -1) {
            if (tile && func_0204bd08(tile)) {
                func_0204f818(&x, &z, &position);
                p2.x = x;
                p2.z = z;
                func_0200bdbc(self, &p2, -1, 6, -1);
                return 1;
            }
        } else if (tile && func_0204bd08(tile)) {
            if (func_020b2300() <= 1) {
                if (func_0200ff28(self, &position, 0, action) && func_0200fd04(self, &position, 1)) {
                    return 1;
                }
            } else {
                func_0204f818(&x, &z, &position);
                p3.x = x;
                p3.z = z;
                func_0200bdbc(self, &p3, -3, 6, -1);
                return 1;
            }
        }
    }
fallback:
    if (WORD(self, 0x170) == 1) {
        func_0200fa1c(&val2, self, VEC(self, 0x5c), (u16 *) (self + 0x8e), &data_ov004_02254aec);
        copyvec(&position, &val2);
    } else {
        position.x = WORD(self, 0x158);
        position.y = WORD(self, 0x15c);
        position.z = WORD(self, 0x160);
        if (!func_0201005c(self, &position, 12)) {
            return 0;
        }
    }
    tile = func_0204f5a8(grid, &position, 0);
    if (tile && func_0204bd08(tile)) {
        if (func_02099fe8() == -1) {
            func_0204f818(&x, &z, &position);
            p4.x = x;
            p4.z = z;
            func_0200bdbc(self, &p4, -1, 6, -1);
            return 1;
        } else {
            if (func_020b2300() <= 1) {
                if (func_0200ff28(self, &position, 0, action) && func_0200fd04(self, &position, 0)) {
                    return 1;
                }
            } else {
                func_0204f818(&x, &z, &position);
                p5.x = x;
                p5.z = z;
                func_0200bdbc(self, &p5, -3, 6, -1);
                return 1;
            }
        }
    }
fail:
    return 0;
}
