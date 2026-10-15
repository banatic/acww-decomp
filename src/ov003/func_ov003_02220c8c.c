/* func_ov003_02220c8c @ 0x02220c8c, 0xc4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020961a8(int a);
extern void func_0204f818(int *a, int *b, void *v);
extern void func_0204f794(int *out, int a, int b);
extern int func_02073d90(void *g);
extern int func_ov003_022213f8(void *p, int x, void *pair, void *vec, int a, int b, int c, int d);

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} Pair;

typedef struct {
    char pad_00[0x5c];
    Vec3 unk_5C;
} Src;
typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02220c8c;

extern UnkStruct_02220c8c *data_020ccf94;
extern int data_ov003_0223cfe4;

int func_ov003_02220c8c(int a0, int a1)
{
    int a, b;
    Pair pp;
    Vec3 v20;
    int out2[3];
    Vec3 vv;
    Src *p;
    Vec3 *sv;
    UnkStruct_02220c8c *g;
    int k, x, t;

    v20.x = 0;
    v20.y = 0;
    v20.z = 0;
    a = 0;
    b = 0;
    p = (Src *) func_020961a8(4);
    if (p != 0) {
        sv = &p->unk_5C;
        t = p->unk_5C.x;
        v20.x = t;
        v20.y = sv->y;
        v20.z = sv->z;
        v20.x = t + ((a1 << 12) >> 4);
        func_0204f818(&a, &b, &v20);
        b = (b / 16) * 16 + 1;
        func_0204f794(out2, a, b);
        v20.z = out2[2];
    }
    v20.y = 0xa000;
    if (a0 == 0) {
        k = 0x156b;
    } else {
        k = 0x137b;
    }
    g = data_020ccf94;
    if (func_02073d90(g) != 0) {
        x = g->unk_64;
    } else {
        x = 0;
    }
    vv.x = v20.x;
    vv.y = v20.y;
    vv.z = v20.z;
    pp.a = a;
    pp.b = b;
    return func_ov003_022213f8(&data_ov003_0223cfe4, x, &pp, &vv, 0xc, k, 0, 0);
}
