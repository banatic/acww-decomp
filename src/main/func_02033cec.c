/* func_02033cec @ 0x02033cec, 0x464 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int w[14];
} Box;

typedef struct Res {
    unsigned char unk_00;
    unsigned char pad_01[3];
    int unk_04, unk_08, unk_0C;
    int unk_10, unk_14, unk_18;
    int unk_1C, unk_20;
    int unk_24, unk_28, unk_2C;
    int unk_30, unk_34, unk_38, unk_3C;
} Res;

typedef struct GG {
    unsigned char pad_00[0x132];
    short unk_132;
    short unk_134;
} GG;

extern GG *data_020da1a8;
extern unsigned char data_020c9098[];
extern unsigned char data_020c9090[];
extern unsigned char data_020c9087[];
extern int data_021c317c;

extern int func_01ffcb2c(int a, int b);
extern int FX_MulFunc(int a, int b);
extern int func_02031da8(Vec3 *v);
extern int func_02031ca8(int a, int b, int c);
extern int func_02031d28(int a, int b, int c);
extern int func_02031c14(int a, int b);
extern void *func_0202feb4(Box *o, Vec3 *p, Vec3 *q, Vec3 *r, int *tbl);
extern int func_0202fb8c(Box *o, Vec3 *v);
extern void func_0202fee0(Box *o);
extern void func_02034150(Res *r, int a, int b, int c);
extern void func_020ea6e0(Vec3 *p, int v);

void func_02033cec(Res *res, Vec3 *v, int fa, int p3)
{
    GG *g;
    int sc;
    int s6;
    int kind;
    int t;
    Vec3 ctr;

    {
        unsigned char *cp = (unsigned char *) &ctr;
        *cp = *cp;
    }
    g = data_020da1a8;
    sc = g->unk_132;
    s6 = g->unk_134;
    res->unk_00 = 0;
    res->unk_10 = v->x;
    res->unk_14 = v->y;
    res->unk_18 = v->z;
    res->unk_1C = v->x >> 13;
    res->unk_20 = v->z >> 13;
    kind = func_01ffcb2c(res->unk_1C, res->unk_20);
    t = func_02031da8(v);
    if (fa != 0) {
        res->unk_34 = func_02031ca8(res->unk_1C, res->unk_20, t);
    } else {
        res->unk_34 = func_02031d28(res->unk_1C, res->unk_20, t);
    }
    res->unk_38 = (res->unk_34 < 0x7c) ? (*(short *) (data_020c9098 + res->unk_34 * 0x1e)) << 8 : 0;
    res->unk_3C = 0xfffee000;
    res->unk_30 = (res->unk_34 < 0x7c) ? data_020c9090[res->unk_34 * 0x1e] : 0;
    res->unk_24 = 0;
    res->unk_28 = 0;
    res->unk_2C = 0x1000;
    if (func_02031c14(res->unk_34, p3) != 0) {
        if (kind == 0x52) {
            Vec3 a, b, c;
            Box out;
            int yy;
            int az;
            int bz;
            int x, y, z;
            ctr.x = (v->x & ~0x1fff) + 0x1000;
            ctr.y = 0;
            ctr.z = (v->z & ~0x1fff) + 0x1000;
            a.x = ctr.x - 0x1000;
            a.y = ctr.y;
            az = ctr.z + 0x1000;
            a.z = az;
            t = FX_MulFunc(s6, 0x1666);
            bz = az - t;
            b.x = a.x;
            yy = a.y;
            b.y = yy;
            b.z = bz;
            t = FX_MulFunc(s6, 0x1666);
            c.x = a.x + t;
            c.y = yy;
            c.z = az;
            func_0202feb4(&out, &b, &a, &c, &data_021c317c);
            if (func_0202fb8c(&out, v) != 0) {
                res->unk_34 = 0x16;
                func_02034150(res, sc, s6, 0x6000);
            } else {
                res->unk_30 = 0;
                res->unk_34 = 0x13;
            }
            res->unk_00 = 1;
            z = (b.z + c.z) >> 1;
            y = (b.y + c.y) >> 1;
            x = (b.x + c.x) >> 1;
            res->unk_04 = x;
            res->unk_08 = y;
            res->unk_0C = z;
            func_0202fee0(&out);
        } else if (kind == 0x55) {
            Vec3 a, b, c;
            Box out;
            int yy;
            int az;
            int bz;
            int u;
            int x, y, z;
            ctr.x = (v->x & ~0x1fff) + 0x1000;
            ctr.y = 0;
            ctr.z = (v->z & ~0x1fff) + 0x1000;
            a.x = ctr.x + 0xb33;
            a.y = ctr.y;
            az = ctr.z - 0xb33;
            a.z = az;
            u = 0x1000 - s6;
            t = FX_MulFunc(u, 0x1666);
            bz = az + t;
            b.x = a.x;
            yy = a.y;
            b.y = yy;
            b.z = bz;
            t = FX_MulFunc(u, 0x1666);
            c.x = a.x - t;
            c.y = yy;
            c.z = az;
            func_0202feb4(&out, &a, &c, &b, &data_021c317c);
            if (func_0202fb8c(&out, v) == 0) {
                res->unk_34 = 0x16;
                func_02034150(res, sc, s6, 0x6000);
            } else {
                res->unk_30 = 0;
                res->unk_34 = 0x13;
            }
            res->unk_00 = 1;
            z = (b.z + c.z) >> 1;
            y = (b.y + c.y) >> 1;
            x = (b.x + c.x) >> 1;
            res->unk_04 = x;
            res->unk_08 = y;
            res->unk_0C = z;
            func_0202fee0(&out);
        } else if (kind == 0x51) {
            Vec3 a, b, c;
            Box out;
            int yy;
            int az;
            int bz;
            int x, y, z;
            ctr.x = (v->x & ~0x1fff) + 0x1000;
            ctr.y = 0;
            ctr.z = (v->z & ~0x1fff) + 0x1000;
            a.x = ctr.x + 0x1000;
            a.y = ctr.y;
            az = ctr.z + 0x1000;
            a.z = az;
            t = FX_MulFunc(s6, 0x1666);
            bz = az - t;
            b.x = a.x;
            yy = a.y;
            b.y = yy;
            b.z = bz;
            t = FX_MulFunc(s6, 0x1666);
            c.x = a.x - t;
            c.y = yy;
            c.z = az;
            func_0202feb4(&out, &b, &c, &a, &data_021c317c);
            if (func_0202fb8c(&out, v) != 0) {
                res->unk_34 = 0x16;
                func_02034150(res, sc, s6, 0xffffa000);
            } else {
                res->unk_30 = 0;
                res->unk_34 = 0x13;
            }
            res->unk_00 = 1;
            z = (b.z + c.z) >> 1;
            y = (b.y + c.y) >> 1;
            x = (b.x + c.x) >> 1;
            res->unk_04 = x;
            res->unk_08 = y;
            res->unk_0C = z;
            func_0202fee0(&out);
        } else if (kind == 0x54) {
            Vec3 a, b, c;
            Box out;
            int yy;
            int az;
            int bz;
            int u;
            int x, y, z;
            ctr.x = (v->x & ~0x1fff) + 0x1000;
            ctr.y = 0;
            ctr.z = (v->z & ~0x1fff) + 0x1000;
            a.x = ctr.x - 0xb33;
            a.y = ctr.y;
            az = ctr.z - 0xb33;
            a.z = az;
            u = 0x1000 - s6;
            t = FX_MulFunc(u, 0x1666);
            bz = az + t;
            b.x = a.x;
            yy = a.y;
            b.y = yy;
            b.z = bz;
            t = FX_MulFunc(u, 0x1666);
            c.x = a.x + t;
            c.y = yy;
            c.z = az;
            func_0202feb4(&out, &a, &b, &c, &data_021c317c);
            if (func_0202fb8c(&out, v) == 0) {
                res->unk_34 = 0x16;
                func_02034150(res, sc, s6, 0xffffa000);
            } else {
                res->unk_30 = 0;
                res->unk_34 = 0x13;
            }
            res->unk_00 = 1;
            z = (b.z + c.z) >> 1;
            y = (b.y + c.y) >> 1;
            x = (b.x + c.x) >> 1;
            res->unk_04 = x;
            res->unk_08 = y;
            res->unk_0C = z;
            func_0202fee0(&out);
        } else if (kind == 0x53) {
            int zz;
            int cz1;
            ctr.x = (v->x & ~0x1fff) + 0x1000;
            ctr.y = 0;
            ctr.z = (v->z & ~0x1fff) + 0x1000;
            cz1 = ctr.z + 0x1000;
            zz = cz1 - FX_MulFunc(s6, 0x1666);
            if (zz > v->z) {
                res->unk_30 = 0;
                res->unk_34 = 0x13;
            } else {
                res->unk_34 = 0x16;
                func_02034150(res, sc, s6, 0xffff8000);
            }
            res->unk_00 = 1;
            res->unk_04 = ctr.x;
            res->unk_08 = 0;
            res->unk_0C = zz;
        } else {
            int m;
            int i;
            int val;
            m = (res->unk_34 < 0x7c) ? data_020c9087[res->unk_34 * 0x1e] : 0;
            if (m != 0) {
                val = 0;
                i = val;
                for (i = 0; i < 8; i++) {
                    if ((m & (1 << i)) != 0) {
                        val = (short) (i << 13);
                        break;
                    }
                }
                func_020ea6e0((Vec3 *) &res->unk_24, val);
            }
        }
        if (res->unk_30 != 0) {
            res->unk_3C = 0xfffff000;
        }
    } else {
        res->unk_30 = 0;
    }
}
