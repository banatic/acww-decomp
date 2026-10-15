/* func_020b1e54 @ 0x020b1e54, 0x3b8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// if/else rather than a ternary for the tile lookup.

typedef struct World {
    void *unk_00;
    int unk_04;
    int unk_08;
} World;

typedef struct UnkStruct_020b1e54 {
    u16 id;
} UnkStruct_020b1e54;

extern int data_021f4b40;
extern u16 data_021f4b28;
extern int data_021f4ba0;
extern void func_020051b0(void *);

extern void __register_global_object(void *, void *, void *);
extern World *func_0204e414(void);
extern int func_02037e84(void *t);
extern int func_02037bd8(unsigned int);
extern UnkStruct_020b1e54 *func_02037e0c(void *t, int a, int b, int c);
extern int func_0204bb00(UnkStruct_020b1e54 *o);
extern int func_0204bba8(UnkStruct_020b1e54 *o);
extern int func_0204bcdc(UnkStruct_020b1e54 *o);
extern int func_0204bc64(void *p);
extern void func_0204f800(int *px, int *py, int a, int b, int c, int d);
extern void *func_020b3b50(UnkStruct_020b1e54 *o);
extern unsigned int func_020b3eb8(void *l);
extern int func_020b3e08(void *l, int *a, int *b, unsigned int k);
extern int func_0204f538(World *w, u16 *st, int x, int y, int f);

void func_020b1e54(void)
{
    // DECLS
    int i;
    int j;
    int res;
    void *list;
    unsigned int n;
    unsigned int k;
    void *tile;
    World *w;
    int m1;
    int m2;
    int m3;
    int flags;
    int kind;
    int x;
    int y;
    UnkStruct_020b1e54 *obj;
    unsigned int f;
    // ENDDECLS
    u16 buf[4];
    int px, py;
    int q[3];

    if ((data_021f4b40 & 1) == 0) {
        data_021f4b28 = 0xfff1;
        __register_global_object((void *) (&data_021f4b28), (((void *) func_020051b0)), (void *) (&data_021f4ba0));
        data_021f4b40 |= 1;
    }
    w = func_0204e414();
    if (w == 0) {
        return;
    }
    for (i = 1; i < w->unk_08; i++) {
        for (j = 1; j < w->unk_04; j++) {
            if ((unsigned int) j < (unsigned int) w->unk_04 && (unsigned int) i < (unsigned int) w->unk_08 && w->unk_00 != 0) {
                tile = (void *) ((char *) w->unk_00 + 0x28 * (j + i * w->unk_04));
            } else {
                tile = (void *) 0;
            }
            kind = func_02037e84(tile);
            flags = func_02037bd8((unsigned int) kind);
            x = 0;
            m1 = flags;
            m1 &= 1;
            m2 = flags;
            m2 &= 2;
            m3 = flags;
            m3 &= 0x800;
            flags &= 0x200;
            for (; x < 0x10; x++) {
                for (y = 0; y < 0x10; y++) {
                    obj = (tile != 0) ? func_02037e0c(tile, y, x, 0) : (UnkStruct_020b1e54 *) 0;
                    if (obj == 0) {
                        continue;
                    }
                    res = 0;
                    if (func_0204bb00(obj)) {
                        if (m1 == 0) {
                            res = 1;
                        } else {
                            int v = x;
                            switch (kind) {
                                case 0x1d:
                                    v = 5;
                                    break;
                                case 0x1e:
                                    v = 5;
                                    break;
                                case 0x1f:
                                    v = 5;
                                    break;
                            }
                            f = (y != 0 && v == x);
                            if (f == 0) {
                                res = 1;
                            }
                        }
                    }
                    if (func_0204bba8(obj)) {
                        if (m2 == 0) {
                            res = 1;
                        } else {
                            int v = x;
                            switch (kind) {
                                case 0x23:
                                    v = 9;
                                    break;
                                case 0x24:
                                    v = 8;
                                    break;
                                case 0x25:
                                    v = 4;
                                    break;
                            }
                            f = (y != 0 && v == x);
                            if (f == 0) {
                                res = 1;
                            }
                        }
                    }
                    if (func_0204bcdc(obj)) {
                        int t;
                        buf[0] = 0x500c;
                        t = func_0204bc64(obj);
                        f = (t == func_0204bc64(&buf[0]));
                    } else {
                        f = (obj->id == 0x500c);
                    }
                    if (f) {
                        if (m2 == 0) {
                            res = 1;
                        } else {
                            int v = x;
                            switch (kind) {
                                case 0x23:
                                    v = 8;
                                    break;
                                case 0x24:
                                    v = 9;
                                    break;
                                case 0x25:
                                    v = 6;
                                    break;
                            }
                            f = (y != 0 && v == x);
                            if (f == 0) {
                                res = 1;
                            }
                        }
                    }
                    if (func_0204bcdc(obj)) {
                        int t;
                        buf[1] = 0x5011;
                        t = func_0204bc64(obj);
                        f = (t == func_0204bc64(&buf[1]));
                    } else {
                        f = (obj->id == 0x5011);
                    }
                    if (f) {
                        if (m3 == 0) {
                            res = 1;
                        } else {
                            int v = x;
                            switch (kind) {
                                case 0x20:
                                    v = 6;
                                    break;
                                case 0x21:
                                    v = 0xa;
                                    break;
                                case 0x22:
                                    v = 5;
                                    break;
                            }
                            f = (y != 0 && v == x);
                            if (f == 0) {
                                res = 1;
                            }
                        }
                    }
                    if (func_0204bcdc(obj)) {
                        int t;
                        buf[2] = 0x5000;
                        t = func_0204bc64(obj);
                        f = (t == func_0204bc64(&buf[2]));
                    } else {
                        f = (obj->id == 0x5000);
                    }
                    if (f) {
                        if (flags == 0) {
                            res = 1;
                        } else {
                            int v = x;
                            switch (kind) {
                                case 0x26:
                                case 0x27:
                                case 0x28:
                                    v = 4;
                                    break;
                            }
                            f = (y != 0 && v == x);
                            if (f == 0) {
                                res = 1;
                            }
                        }
                    }
                    if (res == 0) {
                        continue;
                    }
                    func_0204f800(&px, &py, j, i, y, x);
                    list = func_020b3b50(obj);
                    if (list == 0) {
                        continue;
                    }
                    n = func_020b3eb8(list);
                    for (k = 0; k < n; k++) {
                        q[0] = 0;
                        q[1] = 0;
                        if (func_020b3e08(list, &q[0], &q[1], k)) {
                            func_0204f538(w, &data_021f4b28, px + q[0], py + q[1], 0);
                        }
                    }
                }
            }
        }
    }
}
