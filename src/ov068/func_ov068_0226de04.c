/* func_ov068_0226de04 @ 0x0226de04, 0x204 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    short unk_00;
    short unk_02;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_0226de04;

typedef struct {
    unsigned short a, b;
} UnkStruct_0226de04_2;

extern void VEC_Add(Vec3 *d, int k, Vec3 *s);
extern int func_020e88dc(void *p, int a, int b);
extern int func_020e908c(void *p, Vec3 *v, int a, int b, int c);
extern int func_020e89dc(void *p, int a, int b);
extern int func_0204f490(void *ctx, int *a, int *b, int *c, int *d, unsigned short *e, unsigned short *f, int g, int h);
extern void func_0204f7ac(Vec3 *out, int a, int b, int c, int d);
extern void func_0203be6c(void *self);
extern void func_01ffcbb0(void *dst, void *self);
extern int func_0203c57c(void *self);
extern int func_0203c568(void *self);
extern int func_0203c548(void *self);
extern void func_0203bd84(void *self, void *p, int a, int b, int c);

extern int data_ov068_02277288;
extern int data_ov068_02277280;
extern int data_ov068_02277284;
extern void *data_021c80bc;
extern unsigned short data_ov068_022772d4[][2];
extern int data_ov068_022767cc[];
extern int data_ov068_022772f0[];

typedef struct {
    int a, b, c, d;
} Blk;

void func_ov068_0226de04(void *self)
{
    UnkStruct_0226de04 *s = (UnkStruct_0226de04 *) ((char *) self + 0x21c);
    Vec3 v;
    void *ctx;
    int l18, f1, f2, f3;
    UnkStruct_0226de04_2 e;
    int a2c, a30, a34, a38;
    Vec3 out;
    Blk t54;
    int ta, tb, tc;
    int t1, t2, tw;

    v.x = s->unk_04;
    v.y = s->unk_08;
    v.z = s->unk_0C;
    VEC_Add(&v, s->unk_10, &v);
    func_020e88dc((char *) s + 0x14, data_ov068_02277288, data_ov068_02277280);
    if (func_020e908c((char *) self + 0x110, &v, data_ov068_02277284, s->unk_14, 8) == 0) {
        if (func_020e89dc(s, 0, 1) != 0) {
            s->unk_00 = 0x3c;
            if (func_020e89dc((char *) s + 2, 7, 1) != 0) {
                s->unk_02 = 0;
            }
            ctx = data_021c80bc;
            l18 = 0;
            a2c = 0;
            a30 = 0;
            a34 = 0;
            a38 = 0;
            if (ctx != 0) {
                f1 = l18;
                f2 = l18;
                f3 = l18;
                do {
                    if (data_ov068_022772d4[s->unk_02][0] >= 0x5001 && data_ov068_022772d4[s->unk_02][0] <= 0x5008) {
                        t1 = 1;
                    } else {
                        t1 = f1;
                    }
                    if (t1 != 0) {
                        data_ov068_022772d4[s->unk_02][0]++;
                        if (data_ov068_022772d4[s->unk_02][0] > 0x5008) {
                            data_ov068_022772d4[s->unk_02][0] = 0x5001;
                        }
                        data_ov068_022772d4[s->unk_02][1] = data_ov068_022772d4[s->unk_02][0];
                    } else {
                        if (data_ov068_022772d4[s->unk_02][0] >= 0x500d && data_ov068_022772d4[s->unk_02][0] <= 0x5010) {
                            t2 = 1;
                        } else {
                            t2 = f2;
                        }
                        if (t2 != 0) {
                            data_ov068_022772d4[s->unk_02][0]++;
                            if (data_ov068_022772d4[s->unk_02][0] > 0x5010) {
                                data_ov068_022772d4[s->unk_02][0] = 0x500d;
                            }
                            data_ov068_022772d4[s->unk_02][1] = data_ov068_022772d4[s->unk_02][0];
                            l18 = data_ov068_022772d4[s->unk_02][0] - 0x500d;
                        }
                    }
                    e.a = data_ov068_022772d4[s->unk_02][0];
                    e.b = data_ov068_022772d4[s->unk_02][1];
                } while (func_0204f490(ctx, &a2c, &a30, &a34, &a38, &e.a, &e.b, data_ov068_022767cc[s->unk_02], f3) == 0);
                func_0204f7ac(&out, a2c, a30, a34, a38);
                s->unk_04 = out.x;
                s->unk_08 = out.y;
                s->unk_0C = out.z;
                tw = data_ov068_022772f0[s->unk_02];
                l18 = l18 * 0xc;
                s->unk_10 = tw + l18;
                s->unk_14 = 0;
            }
        }
    }
    func_0203be6c(self);
    func_01ffcbb0(&t54, self);
    ta = func_0203c57c(self);
    tb = func_0203c568(self);
    tc = func_0203c548(self);
    func_0203bd84(self, &t54, ta, tb, tc);
}
