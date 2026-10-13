/* func_02088024 @ 0x02088024, 0x174 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

// Loop-invariant terms are recomputed inside the loop, hence the pragma.

#pragma opt_loop_invariants off

typedef struct UnkStruct_02088024 {
    u16 id;
} UnkStruct_02088024;

extern int func_02078ec0(int x, int z, void *ctx);
extern UnkStruct_02088024 *func_0204f5e0(void *ctx, int cx, int cz, int fx, int fz, int k);
extern int func_0204c71c(UnkStruct_02088024 *e);
extern int func_0204ba94(UnkStruct_02088024 *e);

int func_02088024(int x, int z, void *ctx)
{
    UnkStruct_02088024 *e2;
    int i;
    UnkStruct_02088024 *e;
    u16 v;
    int f;
    int t9, t8, t7, t6;
    int t5, t4, t3, t2, t1;
    int cx;
    int k1, k2, k3;
    int fx;
    int zz, cz;
    int zw, cw;

    if (ctx == 0) {
        goto ret0;
    }
    if (func_02078ec0(x, z, ctx) == 0) {
        goto ret0;
    }
    k1 = 1;
    k2 = 1;
    k3 = 1;
    for (i = 1; i <= 2; i++) {
        zz = z + i;
        cx = x >> 4;
        cz = zz >> 4;
        fx = x - (cx << 4);
        e = func_0204f5e0(ctx, cx, cz, fx, zz - (cz << 4), 0);
        if (e != 0) {
            f = 0;
            v = e->id;
            if (v >= 0x5000 && v <= 0x5021) {
                f = k1;
            }
            if (f == 0) {
                if (func_0204c71c(e) == 0) {
                    if (func_0204ba94(e) != 0) {
                        goto ok;
                    }
                    t2 = t3 = t4 = t5 = t6 = t7 = t8 = t9 = k2;
                    t1 = 0;
                    v = e->id;
                    if (v >= 0x26 && v <= 0x2a) {
                        t1 = t9;
                    }
                    if (t1 == 0) {
                        if (!(v >= 0x5d && v <= 0x61)) {
                            t2 = 0;
                        }
                    }
                    if (t2 == 0) {
                        if (!(v >= 0x2f && v <= 0x56)) {
                            t3 = 0;
                        }
                    }
                    if (t3 == 0) {
                        if (!(v >= 0x57 && v <= 0x5b)) {
                            t4 = 0;
                        }
                    }
                    if (t4 == 0) {
                        if (!(v >= 0x66 && v <= 0x68)) {
                            t5 = 0;
                        }
                    }
                    if (t5 == 0) {
                        if (v != 0x69) {
                            t6 = 0;
                        }
                    }
                    if (t6 == 0) {
                        if (!(v >= 0x6a && v <= 0x6c)) {
                            t7 = 0;
                        }
                    }
                    if (t7 == 0) {
                        if (v != 0x6d) {
                            t8 = 0;
                        }
                    }
                    if (t8 == 0) {
                        if (!(v >= 0xc8 && v <= 0xcf)) {
                            t9 = 0;
                        }
                    }
                    if (t9 == 0) {
                        goto ok;
                    }
                }
            }
        }
        return 0;
    ok:
        zw = z - i;
        cw = zw >> 4;
        e2 = func_0204f5e0(ctx, cx, cw, fx, zw - (cw << 4), 0);
        if (e2 != 0) {
            f = 0;
            v = e2->id;
            if (v >= 0x5000 && v <= 0x5021) {
                f = k3;
            }
            if (f == 0) {
                continue;
            }
        }
        return 0;
    }
    return 1;
ret0:
    return 0;
}

//ITEMS: E *e;|E *e2;|int i;|u16 v;|int f;
