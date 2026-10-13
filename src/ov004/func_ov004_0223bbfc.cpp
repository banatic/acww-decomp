/* func_ov004_0223bbfc @ 0x0223bbfc, 0x1b0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;
struct Actor {
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual void unused3();
    virtual void unused4();
    virtual void unused5();
    virtual void unused6();
    virtual void unused7();
    virtual void unused8();
    virtual void unused9();
    virtual void unused10();
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void unused14();
    virtual void unused15();
    virtual void unused16();
    virtual void unused17();
    virtual void unused18();
    virtual void unused19();
    virtual void unused20();
    virtual void unused21();
    virtual void unused22();
    virtual void unused23();
    virtual void unused24();
    virtual void unused25();
    virtual void unused26();
    virtual void unused27();
    virtual void unused28();
    virtual void unused29();
    virtual void unused30();
    virtual void unused31();
    virtual void unused32();
    virtual void unused33();
    virtual void unused34();
    virtual void unused35();
    virtual void unused36();
    virtual void unused37();
    virtual void unused38();
    virtual void unused39();
    virtual int ready();
};
extern "C" {
extern void *data_021c80bc;
extern short FX_SinCosTable_[];
extern int data_ov004_02247cec[];
extern void func_0204f818(int *, int *, Vec *), func_0204f794(Vec *, int, int), func_ov004_0220e578(u16 *, Actor *);
extern int FX_MulFunc(int, int), func_020ea990(Vec *, Vec *), func_0204bd08(u16 *), func_ov004_0220ebec(Actor *),
    func_ov004_0220fde0(Actor *), func_0204bc50(int, int), func_ov004_0223cd78(void *, Actor *);
extern u16 *func_0204f5a8(void *, Vec *, int), *func_0204f5e0(void *, int, int, int, int, u8);
extern int func_ov004_0223b958(int *, int *, Vec *, int, unsigned);
extern void *func_ov004_0223cd50(void), *func_ov004_0223ce84(void);
extern Actor *func_ov004_0223cc10(void *, int, int, u8);
int func_ov004_0223bbfc(int *outx, int *outy, Vec *pos, int heading, u16 *item, u16 *fallback)
{
    u16 temporary;
    int oldx, oldy, x, y;
    Vec probe, center;
    unsigned pass;
    void *grid;
    int layer;
    if (item) {
        *item = 0xfff1;
    }
    if (fallback) {
        *fallback = 0xfff1;
    }
    func_0204f818(&oldx, &oldy, pos);
    grid = data_021c80bc;
    if (grid) {
        int z;
        int index = ((u16) heading >> 4) * 2;
        z = pos->z + FX_MulFunc(FX_SinCosTable_[index + 1], 0x10cd);
        probe.x = pos->x + FX_MulFunc(FX_SinCosTable_[index], 0x10cd);
        probe.y = 0;
        probe.z = z;
        {
            u16 *p = func_0204f5a8(grid, &probe, 0);
            if (p && func_0204bd08(p)) {
                return -1;
            }
        }
    }
    for (pass = 0; pass < 4; pass++) {
        for (layer = 1; layer >= 0; layer--) {
            if (func_ov004_0223b958(&x, &y, pos, heading, pass)) {
                Actor *actor;
                func_0204f794(&center, x, y);
                if (func_020ea990(pos, &center) > data_ov004_02247cec[layer & 1]) {
                    continue;
                }
                actor = func_ov004_0223cc10(func_ov004_0223cd50(), x, y, (u8) layer);
                *outx = x;
                *outy = y;
                if (actor && actor->ready() && !func_ov004_0220ebec(actor)) {
                    if (item) {
                        func_ov004_0220e578(&temporary, actor);
                        *item = temporary;
                    }
                    if (fallback) {
                        *fallback = func_0204bc50(func_ov004_0220fde0(actor), 0);
                    }
                    return func_ov004_0223cd78(func_ov004_0223ce84(), actor);
                }
                if (layer == 1 && !actor) {
                    // Preserve the ROM load order before splitting acre and tile coordinates.
                    int tx = *(volatile int *) &x, ty = *(volatile int *) &y;
                    int ax = tx >> 4, ay = ty >> 4;
                    u16 *p = func_0204f5e0(grid, ax, ay, tx - (ax << 4), ty - (ay << 4), (u8) layer);
                    if (p && func_0204bd08(p)) {
                        if (item) {
                            *item = *p;
                        }
                        if (fallback) {
                            *fallback = *p;
                        }
                        return -2;
                    }
                }
            }
        }
    }
    return -1;
}
}
