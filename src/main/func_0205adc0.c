/* func_0205adc0 @ 0x0205adc0, 0x100 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_loop_invariants off

extern void MI_CpuFill8(void *dst, int val, int n);
extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_0204bcdc(void *o);
extern int func_02053c68(void *o);
extern int func_020622a0(int a);
extern int func_0205352c(void *o);
extern int func_020534ec(int a);

struct Rect {
    unsigned int unk_00;
    unsigned int z0;
    unsigned int x1;
    unsigned int z1;
};

extern unsigned int data_021c9854[];

int func_0205adc0(struct Rect *p, void *ctx)
{
    unsigned short arr[74];
    int result;
    unsigned char layer;
    int z;
    int x;
    int cx;
    int cz;
    void *o;
    int v;
    int idx;
    unsigned int k;
    unsigned int i;
    unsigned int count;
    unsigned short mask;
    unsigned int scale;

    MI_CpuFill8(arr, 0, sizeof(arr));

    result = 0;
    for (layer = 0; layer < 2; layer++) {
        for (z = p->z0; z <= p->z1; z++) {
            x = p->unk_00;
            if (x <= p->x1) {
                cz = z >> 4;
                for (; x <= p->x1; x++) {
                    cx = x >> 4;
                    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), layer);
                    if (o != 0 && func_0204bcdc(o) != 0) {
                        v = func_02053c68(o);
                        if (func_020622a0(v) == 2) {
                            idx = func_0205352c(o);
                            arr[v] |= (1 << idx);
                        }
                    }
                }
            }
        }
    }

    for (k = 0; k < 74; k++) {
        if (func_020622a0(k) == 2) {
            mask = 0;
            count = func_020534ec(k);
            for (i = 0; i < count; i++) {
                mask |= (1 << i);
            }
            if (arr[k] >= mask) {
                result = 1;
                if ((int) k < 0x4a) {
                    scale = 1000 * count;
                    if (data_021c9854[k] < scale) {
                        data_021c9854[k] = scale;
                    }
                }
            }
        }
    }

    return result;
}
