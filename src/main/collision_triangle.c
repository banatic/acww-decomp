/* collision_triangle: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202fe00 @ 0x0202fe00, 0x68 bytes, Thumb
 * func_0202fd78 @ 0x0202fd78, 0x88 bytes, Thumb
 * func_0202fc94 @ 0x0202fc94, 0xe2 bytes, Thumb
 * func_0202fc5c @ 0x0202fc5c, 0x38 bytes, Thumb
 * func_0202fc18 @ 0x0202fc18, 0x44 bytes, Thumb
 * func_0202fb8c @ 0x0202fb8c, 0x8c bytes, Thumb
 * func_0202fb60 @ 0x0202fb60, 0x2c bytes, Thumb
 * func_0202fb28 @ 0x0202fb28, 0x36 bytes, Thumb
 * func_0202fa9c @ 0x0202fa9c, 0x8c bytes, Thumb
 * func_0202fa10 @ 0x0202fa10, 0x8c bytes, Thumb
 * func_0202f9d0 @ 0x0202f9d0, 0x40 bytes, Thumb
 * func_0202f904 @ 0x0202f904, 0xcc bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    int pad_00[10];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0202fe00;

typedef struct {
    int x;
    int y;
    int z;
} Vec_0202fc94;

struct UnkStruct_0202fc94 {
    int unk_00;
    Vec_0202fc94 unk_04;
    Vec_0202fc94 unk_10;
    Vec_0202fc94 unk_1C;
    Vec_0202fc94 unk_28;
};

struct Seg {
    unsigned char b[0x24];
};

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int head;
    Vec3 v[4];
    int result;
} UnkStruct_0202fc18;

struct UnkStruct_0202fb60 {
    char pad_00[4];
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[24];
    int unk_28;
    int unk_2C;
    int unk_30;
};

struct UnkStruct_0202fb28 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
};

struct UnkStruct_0202fb28_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};

typedef struct {
    int pad_00;
    int arr0[3];
    int arr1[3];
    int arr2[3];
} SrcStruct;

typedef struct {
    unsigned char pad_00[0x28];
    int unk_28;
    int unk_2C;
    int unk_30;
} UnkStruct_0202f904;

extern int FX_MulFunc(int a, int b);
extern void func_01ffd070(int *, int *, int *);
extern int func_0203005c(struct Seg *, Vec_0202fc94 *, Vec_0202fc94 *);
extern int func_0202ffbc(struct Seg *, Vec_0202fc94 *, void *);
extern int func_0202ff14(struct Seg *, void *);
extern int func_020ea838(Vec_0202fc94 *);
extern void func_020eabc8(Vec_0202fc94 *, int);
extern void VEC_Add(void *, Vec_0202fc94 *, void *);
extern void func_02030058(struct Seg *);
extern void func_020ea8c8(int *out, int x, int *v1, int *v2);
extern void func_020eaca0(void *dst, const void *src, unsigned int size);
extern int FX_Div(int a, int b);

int func_0202fb60(struct UnkStruct_0202fb60 *p);
int func_0202fb28(struct UnkStruct_0202fb28 *a, struct UnkStruct_0202fb28_2 *b);
int func_0202f9d0(int a, int b, int c, int d);
int func_0202f904(UnkStruct_0202f904 *s, Vec3 *out, Vec3 *p2, Vec3 *p3);

int func_0202fe00(UnkStruct_0202fe00 *o, Vec *a, Vec *b, int t)
{
    Vec d;
    int ok;

    ok = 0;
    if (func_0202fb28((struct UnkStruct_0202fb28 *) o, (struct UnkStruct_0202fb28_2 *) a) <= 0 && func_0202fb28((struct UnkStruct_0202fb28 *) o, (struct UnkStruct_0202fb28_2 *) b) > 0 && func_0202f9d0((int) o, (int) (&d), (int) a, (int) b)) {
        a->x = d.x + FX_MulFunc(t, o->unk_28);
        a->y = d.y + FX_MulFunc(t, o->unk_2C);
        a->z = d.z + FX_MulFunc(t, o->unk_30);
        ok = 1;
    }
    return ok;
}

int func_0202fd78(int *arg0, int *arg1, int unused, int arg3)
{
    int flag = 0;
    int local4[3];
    int local16[3];
    int r7;

    r7 = func_0202fb28((struct UnkStruct_0202fb28 *) arg0, (struct UnkStruct_0202fb28_2 *) arg1);
    if (r7 < 0) {
        goto end;
    }
    if (r7 > arg3 + 0x200) {
        goto end;
    }
    if (r7 >= arg3) {
        goto flag1;
    }

    func_01ffd070(local4, arg1, arg0 + 10);
    if (func_0202f904((UnkStruct_0202f904 *) arg0, (Vec3 *) local16, (Vec3 *) arg1, (Vec3 *) local4) == 0) {
        goto end;
    }
    if (r7 >= arg3) {
        goto flag2;
    }
    {
        int delta = arg3 - r7;
        arg1[0] += FX_MulFunc(delta, arg0[10]);
        arg1[1] += FX_MulFunc(delta, arg0[11]);
        arg1[2] += FX_MulFunc(delta, arg0[12]);
    }
flag2:
    flag = 1;
    goto end;
flag1:
    flag = 1;
end:
    return flag;
}

int func_0202fc94(struct UnkStruct_0202fc94 *a, void *b, void *c, int d)
{
    int res;
    int n;
    Vec_0202fc94 w;
    Vec_0202fc94 v;
    struct Seg arr[3];
    struct Seg *s;
    Vec_0202fc94 *pv;
    int n0;

    n0 = func_0202fb28((struct UnkStruct_0202fb28 *) a, (struct UnkStruct_0202fb28_2 *) c);
    if (n0 < 0) {
        return 0;
    }
    n0 = func_0202fb28((struct UnkStruct_0202fb28 *) a, (struct UnkStruct_0202fb28_2 *) b);
    if (n0 < 0) {
        return 0;
    }
    res = 0;
    if (n0 < d) {
        func_0203005c(&arr[0], &a->unk_04, &a->unk_10);
        func_0203005c(&arr[1], &a->unk_10, &a->unk_1C);
        func_0203005c(&arr[2], &a->unk_1C, &a->unk_04);
        for (s = &arr[0]; s < &arr[3]; s++) {
            n = func_0202ffbc(s, &w, b);
            if (n >= d) {
                continue;
            }
            if (func_0202ff14(s, b) == 0) {
                continue;
            }
            func_020eaca0((void *) (&v), (const void *) b, (unsigned int) (&w));
            if (func_020ea838(&v) == 0) {
                pv = &a->unk_28;
                v.x = pv->x;
                v.y = pv->y;
                v.z = pv->z;
                func_020eabc8(&v, d);
            } else {
                func_020eabc8(&v, d - n);
            }
            VEC_Add(b, &v, b);
            res = 1;
            break;
        }
        func_02030058(&arr[2]);
        func_02030058(&arr[1]);
        func_02030058(&arr[0]);
    }
    return res;
}

int func_0202fc5c(int a, int b, int c, int d)
{
    int buf1[3];
    int buf2[3];
    int buf3[4];

    func_020eaca0((void *) buf1, (const void *) c, b);
    func_020eaca0((void *) buf2, (const void *) d, b);
    func_020ea8c8(buf3, a, buf1, buf2);
    return func_020ea838((Vec_0202fc94 *) a);
}

int func_0202fc18(UnkStruct_0202fc18 *out, Vec3 *a, Vec3 *b, Vec3 *c, Vec3 *d)
{
    out->v[0].x = a->x;
    out->v[0].y = a->y;
    out->v[0].z = a->z;
    out->v[1].x = b->x;
    out->v[1].y = b->y;
    out->v[1].z = b->z;
    out->v[2].x = c->x;
    out->v[2].y = c->y;
    out->v[2].z = c->z;
    out->v[3].x = d->x;
    out->v[3].y = d->y;
    out->v[3].z = d->z;
    out->result = func_0202fb60((struct UnkStruct_0202fb60 *) out);
    return 1;
}

int func_0202fb8c(void *src, unsigned int size)
{
    int v[3][3];
    int a, b, c;

    func_020eaca0(&v[0], (char *) src + 4, size);
    func_020eaca0(&v[1], (char *) src + 0x10, size);
    func_020eaca0(&v[2], (char *) src + 0x1c, size);

    a = FX_MulFunc(v[0][2], v[1][0]) - FX_MulFunc(v[0][0], v[1][2]);
    b = FX_MulFunc(v[1][2], v[2][0]) - FX_MulFunc(v[1][0], v[2][2]);
    c = FX_MulFunc(v[2][2], v[0][0]) - FX_MulFunc(v[2][0], v[0][2]);

    if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0)) {
        return 1;
    }
    return 0;
}

int func_0202fb60(struct UnkStruct_0202fb60 *p)
{
    int v1, v2, v3;
    v1 = FX_MulFunc(p->unk_30, (int) p->unk_0C);
    v2 = FX_MulFunc(p->unk_28, (int) p->unk_04);
    v3 = FX_MulFunc(p->unk_2C, (int) p->unk_08);
    return -(v1 + (v2 + v3));
}

int func_0202fb28(struct UnkStruct_0202fb28 *a, struct UnkStruct_0202fb28_2 *b)
{
    int t0 = a->unk_34;
    int t1 = (int __arm) FX_MulFunc(a->unk_30, b->unk_08);
    int t2 = (int __arm) FX_MulFunc(a->unk_28, b->unk_00);
    int t3 = (int __arm) FX_MulFunc(a->unk_2C, b->unk_04);
    return t0 + (t1 + (t2 + t3));
}

int func_0202fa9c(const SrcStruct *src, int size)
{
    int X[3], Y[3], Z[3];
    int d1, d2, d3;

    func_020eaca0(X, &src->arr0[0], size);
    func_020eaca0(Y, &src->arr1[0], size);
    func_020eaca0(Z, &src->arr2[0], size);

    d1 = FX_MulFunc(X[0], Y[1]) - FX_MulFunc(X[1], Y[0]);
    d2 = FX_MulFunc(Y[0], Z[1]) - FX_MulFunc(Y[1], Z[0]);
    d3 = FX_MulFunc(Z[0], X[1]) - FX_MulFunc(Z[1], X[0]);

    if ((d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0)) {
        return 1;
    } else {
        return 0;
    }
}

int func_0202fa10(void *src, unsigned int size)
{
    int v[3][3];
    int a, b, c;

    func_020eaca0(&v[0], (char *) src + 4, size);
    func_020eaca0(&v[1], (char *) src + 0x10, size);
    func_020eaca0(&v[2], (char *) src + 0x1c, size);

    a = FX_MulFunc(v[0][1], v[1][2]) - FX_MulFunc(v[0][2], v[1][1]);
    b = FX_MulFunc(v[1][1], v[2][2]) - FX_MulFunc(v[1][2], v[2][1]);
    c = FX_MulFunc(v[2][1], v[0][2]) - FX_MulFunc(v[2][2], v[0][1]);

    if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0)) {
        return 1;
    }
    return 0;
}

int func_0202f9d0(int a, int b, int c, int d)
{
    int e;
    int f;

    e = func_0202fb28((struct UnkStruct_0202fb28 *) a, (struct UnkStruct_0202fb28_2 *) c);
    f = func_0202fb28((struct UnkStruct_0202fb28 *) a, (struct UnkStruct_0202fb28_2 *) d);
    if (FX_MulFunc(e, f) < 0) {
        return func_0202f904((UnkStruct_0202f904 *) a, (Vec3 *) b, (Vec3 *) c, (Vec3 *) d);
    }
    return 0;
}

int func_0202f904(UnkStruct_0202f904 *s, Vec3 *out, Vec3 *p2, Vec3 *p3)
{
    Vec3 v;
    int t1;
    int diff;
    int ad;
    int k;
    int yy, zz;
    int t;

    t1 = func_0202fb28((struct UnkStruct_0202fb28 *) s, (struct UnkStruct_0202fb28_2 *) p2);
    diff = t1 - func_0202fb28((struct UnkStruct_0202fb28 *) s, (struct UnkStruct_0202fb28_2 *) p3);
    ad = diff < 0 ? -diff : diff;
    if (ad >= 4) {
        func_020eaca0((void *) (&v), (const void *) p3, (unsigned int) p2);
        k = FX_Div(t1, diff);
        zz = p2->z + FX_MulFunc(k, v.z);
        yy = p2->y + FX_MulFunc(k, v.y);
        out->x = p2->x + FX_MulFunc(k, v.x);
        out->y = yy;
        out->z = zz;
        t = s->unk_2C;
        if (t < 0) {
            t = -t;
        }
        if (t >= 4) {
            if (func_0202fb8c((void *) s, (unsigned int) out) != 0) {
                return 1;
            }
        }
        t = s->unk_28;
        if (t < 0) {
            t = -t;
        }
        if (t >= 4) {
            if (func_0202fa10((void *) s, (unsigned int) out) != 0) {
                return 1;
            }
        }
        t = s->unk_30;
        if (t < 0) {
            t = -t;
        }
        if (t >= 4) {
            if (func_0202fa9c((const SrcStruct *) s, (int) out) != 0) {
                return 1;
            }
        }
    }
    return 0;
}
