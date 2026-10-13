/* func_ov003_022235d8 @ 0x022235d8, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern char *data_ov003_0223cf70;

extern void *func_0204e414(void);
extern void *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int k);
extern int func_02073d90(void *);
extern int func_0204b7a0(void *p);

struct Vec {
    int x;
    int z;
};

struct UnkStruct_022235d8 {
    char pad_00[4];
    int unk_04;
    char pad_08[0xb0];
    unsigned char unk_B8;
    char pad_B9[0x13];
    int unk_CC;
    int unk_D0;
};

extern struct UnkStruct_022235d8 *func_ov003_02223870(void *a, void *b, int c, int d);

void func_ov003_022235d8(int a0, struct Vec *v)
{
    void *ctx;
    void *obj;
    struct UnkStruct_022235d8 *p;
    int n;
    int cx;
    int cz;
    int x;
    int z;

    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    x = v->x;
    z = v->z;
    cx = x >> 4;
    cz = z >> 4;
    obj = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (obj == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) == 0) {
        a0 = 0;
    }
    n = func_0204b7a0(obj);
    if (n <= 0 || n > 4) {
        return;
    }
    p = func_ov003_02223870(data_ov003_0223cf70 + 0x4b20, obj, n - 1, (v->x ^ v->z) & 1);
    if (p == 0) {
        return;
    }
    if (v->x != p->unk_CC) {
        return;
    }
    if (v->z != p->unk_D0) {
        return;
    }
    if (a0 != p->unk_04) {
        return;
    }
    p->unk_B8 = 0;
}
