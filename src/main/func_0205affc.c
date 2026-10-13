/* func_0205affc @ 0x0205affc, 0x274 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

typedef struct {
    unsigned int unk_00;
    unsigned int z0;
    unsigned int x1;
    unsigned int z1;
    unsigned short unk_10;
    unsigned short unk_12;
} Rect;

extern void MI_CpuFill8(void *dst, int fill, unsigned int len);
extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *p);
extern int func_02053c68(void *p);
extern int func_020622a0(int i);
extern int func_0205352c(void *p);
extern int func_02062998(void *p);

extern unsigned int data_021c9854[];
extern unsigned short data_020cbff0;
extern unsigned short data_020cbff4;

int func_0205affc(Rect *r, void *ctx, unsigned int *out)
{

    unsigned int best;
    int cz;
    void *o;
    int v;
    unsigned short bits[74];
    unsigned char layer;
    int z, x;
    int cx;
    int idx;
    unsigned int ok1;
    unsigned short w;
    unsigned int k;
    unsigned int i;
    unsigned int n;
    unsigned int j;
    int h;
    unsigned int lim;
    unsigned int found;
    unsigned int ok;

    MI_CpuFill8(bits, 0, 0x94);

    best = 0;
    layer = 0;
    do {
        for (z = r->z0; z <= r->z1; z++) {
            x = r->unk_00;
            if (x <= r->x1) {
                cz = z >> 4;
                for (; x <= r->x1; x++) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o == 0) {
                        continue;
                    }
                    if (func_0204bcdc(o) == 0) {
                        continue;
                    }
                    v = func_02053c68(o);
                    if (func_020622a0(v) != 0) {
                        continue;
                    }
                    idx = func_0205352c(o);
                    bits[v] |= (1 << idx);
                }
            }
        }
        layer++;
    } while (layer < 2);

    ok1 = 0;
    w = r->unk_10;
    if (w >= 0x1100 && w <= 0x1143) {
        ok1 = 1;
    }
    if (ok1 > 0) {
        k = func_02062998(&r->unk_10);
        if (func_020622a0(k) == 0) {
            bits[k] |= data_020cbff0;
        }
    }

    ok1 = 0;
    w = r->unk_12;
    if (w >= 0x1144 && w <= 0x1187) {
        ok1 = 1;
    }
    if (ok1 > 0) {
        k = func_02062998(&r->unk_12);
        if (func_020622a0(k) == 0) {
            bits[k] |= data_020cbff4;
        }
    }

    i = 0;
    found = 0;
    for (; i < 0x4a; i++) {
        if (func_020622a0(func_02062998(&r->unk_12)) != 0) {
            continue;
        }
        n = found;
        j = found;
        h = bits[i];
        for (; j < 0xc; j++) {
            if (((h >> j) & 1) != 0) {
                n++;
            }
        }
        if (n > best) {
            best = n;
        }
    }

    if (out != 0) {
        *out = best;
    }

    i = 0;
    found = 0;
    lim = 0x7530;
    for (; i < 0x4a; i++) {
        if (func_020622a0(i) != 0) {
            continue;
        }
        if (bits[i] != 0xfff) {
            continue;
        }
        if ((int) i < 0x4a && data_021c9854[i] < lim) {
            data_021c9854[i] = lim;
            ok = 1;
        } else {
            ok = found;
        }
        if (ok != 0) {
            return i;
        }
    }

    i = 0;
    found = 0;
    lim = 0x61a8;
    for (; i < 0x4a; i++) {
        if (func_020622a0(i) != 0) {
            continue;
        }
        h = bits[i];
        if ((h & 0x3ff) != 0x3ff) {
            continue;
        }
        if ((h & 0x400) == 0) {
            if ((h & 0x800) == 0) {
                continue;
            }
        }
        if ((int) i < 0x4a && data_021c9854[i] < lim) {
            data_021c9854[i] = lim;
            ok = 1;
        } else {
            ok = found;
        }
        if (ok != 0) {
            return 0x4a;
        }
    }

    i = 0;
    found = 0;
    lim = 0x4e20;
    for (; i < 0x4a; i++) {
        if (func_020622a0(i) != 0) {
            continue;
        }
        if (bits[i] != 0x3ff) {
            continue;
        }
        if ((int) i < 0x4a && data_021c9854[i] < lim) {
            data_021c9854[i] = lim;
            ok = 1;
        } else {
            ok = found;
        }
        if (ok != 0) {
            return 0x4a;
        }
    }

    return 0x4a;
}
