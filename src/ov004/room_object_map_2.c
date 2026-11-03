/* room_object_map_2: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220f240 @ 0x0220f240, 0x3c bytes, Thumb
 * func_ov004_0220f218 @ 0x0220f218, 0x28 bytes, Thumb
 * func_ov004_0220f100 @ 0x0220f100, 0x118 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0220f100 {
    int x;
    int y;
};

extern int func_0204bc50(int argument0, int argument1);
extern int func_ov004_0220e5c8(void *self);
extern char *func_ov004_0220db94(void *it);
extern void func_ov004_0220f27c(void *self, void *it, int a, int b);
extern unsigned char func_020b65c4(void);
extern unsigned char func_ov004_0223d348(void);
extern struct UnkStruct_0220f100 *func_ov004_0220db5c(void *it, unsigned int i);
extern unsigned int func_ov004_0220db68(void *it);
extern void func_ov004_0220db90(void *it);
extern void *func_0204f5e0(void *g, int qx, int qy, int rx, int ry, int k);
extern int func_0204bcdc(void *p);
extern unsigned char func_ov004_0220d2b8(void *p);
extern void func_020521d8(int region, int x, int y, int kind, int mode, unsigned short *tile, int notify, unsigned char flag);
extern void *func_ov004_0223cd50(void);
extern int func_ov004_0223cc80(void *a, void *self, int x, int y, int k);
extern int func_ov004_0223cc5c(void *a, int x, int y, int k);
extern void *data_021c80bc;

int func_ov004_0220f240(int x)
{
    u16 v = (u16) x;

    if (v >= 0xe000 || v < 0x2000) {
        return 0;
    }
    if (v < 0x6000) {
        return 1;
    }
    if (v < 0xa000) {
        return 2;
    }
    return 3;
}

int func_ov004_0220f218(char *self, char *a1, int a2)
{
    // DECLS
    int v3;
    // ENDDECLS
    v3 = func_0204bc50(*(int *) (a1 + 0x284), func_ov004_0220f240((int) ((int) (a2))));
    *(u16 *) (self) = v3;
    return v3;
}

void func_ov004_0220f100(void *self, unsigned char a1, int a2)
{
    // DECLS
    void *g;
    void *item;
    int t;
    int x;
    int y;
    int qx;
    int qy;
    unsigned int i;
    // ENDDECLS
    int it[10];
    volatile u16 sent;

    if (func_ov004_0220e5c8(self) != 0) {
        return;
    }
    func_ov004_0220db94(it);
    func_ov004_0220f27c(self, it, 0, 0);
    g = data_021c80bc;
    sent = 0xfff1;
    func_020b65c4();
    func_ov004_0223d348();
    for (i = 0; i < func_ov004_0220db68(it); i++) {
        x = func_ov004_0220db5c(it, i)->x;
        y = func_ov004_0220db5c(it, i)->y;
        qx = x >> 4;
        qy = y >> 4;
        item = func_0204f5e0(g, qx, qy, x - (qx << 4), y - (qy << 4), *(u8 *) ((char *) self + 0x288));
        if (item != 0 && func_0204bcdc(item) != 0) {
            t = func_020b65c4();
            func_020521d8(t, x, y, *(u8 *) ((char *) self + 0x288), func_ov004_0220d2b8((char *) self + 0x740),
                          (unsigned short *) item, a2, a1);
        }
        func_ov004_0223cc80(func_ov004_0223cd50(), self, x, y, *(u8 *) ((char *) self + 0x288));
        if (a2 != 0 && *(u8 *) ((char *) self + 0x288) == 0 && func_ov004_0223cc5c(func_ov004_0223cd50(), x, y, 1) != -1) {
            func_ov004_0223cc80(func_ov004_0223cd50(), self, x, y, 1);
        }
    }
    func_ov004_0220db90(it);
}
