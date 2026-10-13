/* func_02044f3c @ 0x02044f3c, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#pragma opt_loop_invariants off

typedef struct {
    int x;
    int z;
} Pt;
typedef struct {
    u8 f0 : 1;
    u8 f1 : 2;
    u8 kind : 5;
    u8 m0 : 7;
    u8 m7 : 1;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06[3];
} UnkStruct_02044f3c;

extern void *data_021c80bc;
extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern void func_02045e24(Pt *pt, int flag);

void func_02044f3c(UnkStruct_02044f3c *p)
{
    volatile u16 tmp;
    Pt a;
    Pt b;
    int x, z;
    int cx, cz;
    void *ctx;
    int i;

    x = p->unk_02 >> 8;
    z = p->unk_02 & 0xff;
    switch (p->kind) {
        case 0xc:
        case 0xd:
        case 0xf:
        case 0x17:
            return;
    }
    ctx = data_021c80bc;
    if (ctx != 0) {
        cx = x >> 4;
        cz = z >> 4;
        func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    }
    {
        int fl = p->m7;
        a.x = x;
        a.z = z;
        func_02045e24(&a, fl);
    }
    if (p->f0 == 0) {
        return;
    }
    for (i = 0; i < 3; i++) {
        u16 *w = (u16 *) ((int) p + 6);
        int xx = w[i] >> 8;
        int zz = w[i] & 0xff;
        tmp = p->unk_06[i];
        if (tmp != 0xffff) {
            int fl = p->m7;
            b.x = xx;
            b.z = zz;
            func_02045e24(&b, fl);
        }
    }
}
