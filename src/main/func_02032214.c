/* func_02032214 @ 0x02032214, 0x218 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} Pair;

typedef struct UnkStruct_02032214 UnkStruct_02032214;
struct UnkStruct_02032214 {
    int unk_00;
    Vec3 unk_04;
    Vec3 unk_10;
    Vec3 unk_1C;
    short unk_28;
    short unk_2A;
    UnkStruct_02032214 *unk_2C;
    Vec3 unk_30[4];
    Pair unk_60[4];
    Vec3 unk_80;
    Vec3 unk_8C;
    char unk_98;
};

extern int data_021fbe48[];

extern int func_020eaa2c(Vec3 *a, Vec3 *b);
extern void func_020e96c8(void *m, int x, int y, int z);
extern void func_020e9744(void *m, int a);
extern void func_020e9838(void *m, int x, int y, int z);
extern void MTX_MultVec43(Vec3 *src, void *m, Vec3 *dst);
extern void func_02031e28(Vec3 *dst, Vec3 *src);
extern void func_02031e08(Vec3 *dst, Vec3 *src);
extern void func_0202f8fc(Pair *p, int a, int b);
extern void func_0202f7cc(Pair *p, int a);

int func_02032214(UnkStruct_02032214 *self, Vec3 *src1, short d, Vec3 *src2)
{
    Vec3 corners[4];
    Vec3 mx, mn;
    Vec3 *p;
    Vec3 *w;
    Vec3 *e;
    Pair *q;
    int hx, hy, zz;
    int i, k;
    int cx, cy, cz, ex, ey, ez;

    if (d == self->unk_28 && func_020eaa2c(&self->unk_04, src1) == 0 && func_020eaa2c(&self->unk_1C, src2) == 0) {
        goto fail;
    }

    self->unk_04.x = src1->x;
    self->unk_04.y = src1->y;
    self->unk_04.z = src1->z;
    self->unk_1C.x = src2->x;
    self->unk_1C.y = src2->y;
    self->unk_1C.z = src2->z;
    self->unk_28 = d;

    hx = self->unk_10.x >> 1;
    hy = self->unk_10.y >> 1;
    zz = self->unk_10.z;

    w = &corners[0];
    w->x = -hx;
    w->y = zz;
    w->z = hy;
    w = &corners[1];
    w->x = hx;
    w->y = zz;
    w->z = hy;
    w = &corners[2];
    w->x = hx;
    w->y = zz;
    w->z = -hy;
    w = &corners[3];
    w->x = -hx;
    w->y = zz;
    w->z = -hy;

    func_020e96c8(data_021fbe48, src1->x, src1->y, src1->z);
    func_020e9744(data_021fbe48, d);
    func_020e9838(data_021fbe48, src2->x, src2->y, src2->z);

    p = &corners[0];
    e = &self->unk_30[0];
    q = &self->unk_60[0];

    if (self->unk_10.x == 0 || self->unk_10.y == 0) {
        k = 1;
        if (self->unk_10.y == 0) {
            k = 0;
        }
        self->unk_2A = 2;
        for (i = 0; i < 4; i++) {
            if ((i & 1) == k) {
                MTX_MultVec43(p, data_021fbe48, e);
                if (i == k) {
                    mx.x = e->x;
                    mx.y = e->y;
                    mx.z = e->z;
                    mn.x = e->x;
                    mn.y = e->y;
                    mn.z = e->z;
                } else {
                    func_02031e28(&mx, e);
                    func_02031e08(&mn, e);
                }
                func_0202f8fc(q, 0, 0x1000);
                func_0202f7cc(q, (short) (d + (i << 14)));
                e++;
                q++;
            }
            p++;
        }
    } else {
        self->unk_2A = 4;
        for (i = 0; i < self->unk_2A; i++) {
            MTX_MultVec43(p, data_021fbe48, e);
            if (i == 0) {
                mx.x = e->x;
                mx.y = e->y;
                mx.z = e->z;
                mn.x = e->x;
                mn.y = e->y;
                mn.z = e->z;
            } else {
                func_02031e28(&mx, e);
                func_02031e08(&mn, e);
            }
            func_0202f8fc(q, 0, 0x1000);
            func_0202f7cc(q, (short) (d + (i << 14)));
            e++;
            p++;
            q++;
        }
    }

    cz = (mx.z + mn.z) >> 1;
    cy = (mx.y + mn.y) >> 1;
    cx = (mx.x + mn.x) >> 1;
    self->unk_80.x = cx;
    self->unk_80.y = cy;
    self->unk_80.z = cz;
    ez = mx.z - self->unk_80.z;
    ey = mx.y - self->unk_80.y;
    ex = mx.x - self->unk_80.x;
    self->unk_8C.x = ex;
    self->unk_8C.y = ey;
    self->unk_8C.z = ez;
    return 1;
fail:
    return 0;
}
