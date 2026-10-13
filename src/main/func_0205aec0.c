/* func_0205aec0 @ 0x0205aec0, 0x13c bytes, Thumb, module main
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
extern int func_02062998(void *p);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *p);
extern int func_02053c68(void *p);
extern int func_020622a0(int i);
extern int func_0205352c(void *p);
extern int func_020534ec(int i);
extern unsigned int data_021c9854[];

int func_0205aec0(Rect *r, void *ctx)
{
    int c, d;
    unsigned char layer;
    int z, x;
    int cx, cz;
    unsigned short *o;
    int idx;
    int result;
    unsigned int i, j;
    int n;
    unsigned int v;
    unsigned short mask;
    unsigned short bits[74];

    MI_CpuFill8(bits, 0, 0x94);
    c = func_02062998(&r->unk_10);
    d = func_02062998(&r->unk_12);
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
                    idx = func_02053c68(o);
                    if (func_020622a0(idx) != 1) {
                        continue;
                    }
                    bits[idx] |= 1 << func_0205352c(o);
                }
            }
        }
        layer++;
    } while (layer < 2);

    result = 0;
    for (i = 0; i < 0x4a; i++) {
        if (func_020622a0(i) != 1) {
            continue;
        }
        mask = 0;
        n = func_020534ec(i);
        for (j = 0; j < n; j++) {
            mask |= 1 << j;
        }
        if (bits[i] >= mask) {
            if (i == c && i == d) {
                if ((int) i < 0x4a) {
                    v = 3000 * (n + 1);
                    if (data_021c9854[i] < v) {
                        data_021c9854[i] = v;
                    }
                }
                result = 1;
            }
        } else {
            if (i == c && i == d && (int) i < 0x4a) {
                if (data_021c9854[i] < 3000) {
                    data_021c9854[i] = 3000;
                }
            }
        }
    }
    return result;
}
