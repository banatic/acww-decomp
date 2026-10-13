/* func_0207172c @ 0x0207172c, 0x37c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// The division is signed, so it calls the division helper.

typedef struct World {
    void *unk_00;
    int unk_04;
    int unk_08;
} World;

typedef struct UnkStruct_0207172c {
    u16 id;
} UnkStruct_0207172c;

extern int data_021d0488;
extern u16 data_021d046c;
extern int data_021d048c;
extern int data_021ebcd4;
extern void func_020051b0(void *p);

extern void __register_global_object(void *o, void (*d)(void *), void *n);
extern World *func_0204e414(void);
extern UnkStruct_0207172c *func_02037e0c(void *t, int a, int b, int c);
extern void func_02037e44(void *t, u16 *p, int a, int b, int c);
extern World *func_0204df30(int i);
extern void *func_02060ee0(void *g, int i);
extern UnkStruct_0207172c *func_02061204(void *e, int k);
extern void func_020611bc(void *e, u16 *p, int k);
extern UnkStruct_0207172c *func_020611e8(void *e, int k);
extern void func_02061194(void *e, u16 *p, int k);

static __inline void *tile_at(World *p, int x, int y)
{
    void *t;
    if ((unsigned int) x < (unsigned int) p->unk_04 && (unsigned int) y < (unsigned int) p->unk_08 && p->unk_00 != 0) {
        t = (void *) ((char *) p->unk_00 + 0x28 * (x + y * p->unk_04));
    } else {
        t = (void *) 0;
    }
    return t;
}

void func_0207172c(int arg)
{
    // DECLS
    int a;
    int b;
    int i;
    void *tile;
    World *w;
    void *q;
    World *p;
    void *e;
    UnkStruct_0207172c *obj;
    unsigned int f;
    int y;
    int x;
    unsigned int id;
    int v;
    int y2;
    int x2;
    // ENDDECLS
    u16 buf[4];

    if ((data_021d0488 & 1) == 0) {
        data_021d046c = 0xfff1;
        __register_global_object(&data_021d046c, func_020051b0, &data_021d048c);
        data_021d0488 |= 1;
    }
    w = func_0204e414();
    if (w != 0) {
        for (y = 1; y < w->unk_08 - 1; y++) {
            for (x = 1; x < w->unk_04 - 1; x++) {
                if ((unsigned int) x < (unsigned int) w->unk_04 && (unsigned int) y < (unsigned int) w->unk_08 &&
                    w->unk_00 != 0) {
                    tile = (void *) ((char *) w->unk_00 + 0x28 * (x + y * w->unk_04));
                } else {
                    tile = (void *) 0;
                }
                if (tile == 0) {
                    continue;
                }
                for (a = 0; a < 0x10; a++) {
                    for (b = 0; b < 0x10; b++) {
                        obj = func_02037e0c(tile, b, a, 0);
                        if (obj == 0) {
                            continue;
                        }
                        f = 0;
                        id = obj->id;
                        if (id >= 0xa7 && id <= 0xc6) {
                            f = 1;
                        }
                        if (f == 0) {
                            continue;
                        }
                        if (arg == ((int) id - 0xa7) / 8) {
                            func_02037e44(tile, &data_021d046c, b, a, 0);
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 5; i++) {
        p = func_0204df30(i);
        if (p != 0) {
            q = tile_at(p, 0, 0);
            if (q != 0) {
                for (y2 = 0; y2 < 0x10; y2++) {
                    for (x2 = 0; x2 < 0x10; x2++) {
                        obj = func_02037e0c(q, x2, y2, 0);
                        if (obj == 0) {
                            continue;
                        }
                        f = 0;
                        id = obj->id;
                        if (id >= 0x3d84 && id <= 0x3e03) {
                            f = 1;
                        }
                        if (f != 0) {
                            v = (id >= 0x3d84 && id <= 0x3e03) ? (int) (id - 0x3d84) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        } else if (id >= 0x3ea4 && id <= 0x3f23) {
                            v = (id >= 0x3ea4 && id <= 0x3f23) ? (int) (id - 0x3ea4) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        } else if (id >= 0x3f24 && id <= 0x3fa3) {
                            v = (id >= 0x3f24 && id <= 0x3fa3) ? (int) (id - 0x3f24) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        } else if (id >= 0x4224 && id <= 0x42a3) {
                            v = (id >= 0x4224 && id <= 0x42a3) ? (int) (id - 0x4224) >> 2 : -1;
                            if (((v >> 3) & 3) == arg) {
                                func_02037e44(q, &data_021d046c, x2, y2, 0);
                            }
                        }
                    }
                }
            }
        }
        e = func_02060ee0(&data_021ebcd4, i);
        if (e == 0) {
            continue;
        }
        obj = func_02061204(e, 0);
        f = 0;
        id = obj->id;
        if (id >= 0x1188 && id <= 0x11a7) {
            f = 1;
        }
        if (f != 0) {
            obj = func_02061204(e, 0);
            f = 0;
            id = obj->id;
            if (id >= 0x1188 && id <= 0x11a7) {
                f = 1;
            }
            v = f ? (int) (id - 0x1188) : -1;
            if (((v >> 3) & 3) == arg) {
                buf[0] = 0x113e;
                func_020611bc(e, &buf[0], 0);
            }
        }
        obj = func_020611e8(e, 0);
        f = 0;
        id = obj->id;
        if (id >= 0x1188 && id <= 0x11a7) {
            f = 1;
        }
        if (f == 0) {
            continue;
        }
        obj = func_020611e8(e, 0);
        f = 0;
        id = obj->id;
        if (id >= 0x1188 && id <= 0x11a7) {
            f = 1;
        }
        v = f ? (int) (id - 0x1188) : -1;
        if (((v >> 3) & 3) == arg) {
            buf[1] = 0x1182;
            func_02061194(e, &buf[1], 0);
        }
    }
}
