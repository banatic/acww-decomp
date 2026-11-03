/* collision_segment_2: 19 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202f8fc @ 0x0202f8fc, 0x6 bytes, Thumb
 * func_0202f8e4 @ 0x0202f8e4, 0x16 bytes, Thumb
 * func_0202f8c8 @ 0x0202f8c8, 0x1a bytes, Thumb
 * func_0202f8b4 @ 0x0202f8b4, 0x12 bytes, Thumb
 * func_0202f898 @ 0x0202f898, 0x1a bytes, Thumb
 * func_0202f874 @ 0x0202f874, 0x24 bytes, Thumb
 * func_0202f838 @ 0x0202f838, 0x3a bytes, Thumb
 * func_0202f7f4 @ 0x0202f7f4, 0x44 bytes, Thumb
 * func_0202f7cc @ 0x0202f7cc, 0x28 bytes, Thumb
 * func_0202f7a0 @ 0x0202f7a0, 0x2a bytes, Thumb
 * func_0202f740 @ 0x0202f740, 0x60 bytes, Thumb
 * func_0202f6f4 @ 0x0202f6f4, 0x4c bytes, Thumb
 * func_0202f6e8 @ 0x0202f6e8, 0xc bytes, Thumb
 * func_0202f6dc @ 0x0202f6dc, 0xc bytes, Thumb
 * func_0202f6ac @ 0x0202f6ac, 0x30 bytes, Thumb
 * func_0202f688 @ 0x0202f688, 0x24 bytes, Thumb
 * func_0202f660 @ 0x0202f660, 0x28 bytes, Thumb
 * func_0202f59c @ 0x0202f59c, 0xc4 bytes, Thumb
 * func_0202f520 @ 0x0202f520, 0x7a bytes, Thumb
 */

struct Pair {
    int x;
    int y;
};

struct Vec2 {
    int x;
    int y;
};

typedef struct {
    unsigned int x;
    unsigned int y;
} UnkStruct_0202f740;

typedef struct {
    void *unk_00;
    UnkStruct_0202f740 arr[3];
} UnkStruct_0202f740_2;

struct UnkStruct_0202f6f4 {
    int unk_00;
    int unk_04;
};

struct UnkStruct_0202f6f4_2 {
    int unk_00;
    struct UnkStruct_0202f6f4 unk_04;
    struct UnkStruct_0202f6f4 unk_0C;
    struct UnkStruct_0202f6f4 unk_14;
};

struct UnkStruct_0202f6ac {
    unsigned char unk_00[4];
    int unk_04;
    unsigned char unk_08[4];
    int unk_0C;
    unsigned char unk_10[4];
    int unk_14;
    unsigned char unk_18[4];
    int unk_1C;
};

typedef struct {
    int pad_00;
    int unk_04;
    int unk_08;
    int pad_0C;
    int pad_10;
    int unk_14;
    int unk_18;
} UnkStruct_0202f688;

struct s0 {
    char pad_00[0x14];
    int unk_14;
    int unk_18;
    int unk_1C;
};

struct s1 {
    int unk_00;
    int unk_04;
};

typedef struct {
    int pad_00[5];
    int a, b, c;
} UnkStruct_0202f59c;

typedef struct {
    int x, y;
} UnkStruct_0202f59c_2;

extern int FX_MulFunc(int, int);
extern int FX_Sqrt(int value);
extern int FX_Div(int a, int b);
extern unsigned char data_021c30b8[];
extern void func_020ea6e0(void *, int);
extern unsigned char data_020da1a4[];

void func_0202f6ac(struct UnkStruct_0202f6ac *a, int b, int c, int d);
int func_0202f688(UnkStruct_0202f688 *data);

void func_0202f8fc(int *p, int a, int b)
{
    p[0] = a;
    p[1] = b;
}

void *func_0202f8e4(void *a, unsigned int *b)
{
    func_0202f8fc((int *) a, b[0], b[1]);
    return a;
}

void func_0202f8c8(int a, int *b, int *c)
{
    func_0202f8fc((int *) a, b[0] + c[0], b[1] + c[1]);
}

void func_0202f8b4(void *a, void *b)
{
    unsigned int *p1 = (unsigned int *) a;
    unsigned int *p2 = (unsigned int *) b;
    unsigned int temp;

    temp = *p1 + *p2;
    *p1 = temp;
    temp = *(p1 + 1) + *(p2 + 1);
    *(p1 + 1) = temp;
}

void func_0202f898(int a, struct Pair *p1, struct Pair *p2)
{
    func_0202f8fc((int *) a, p1->x - p2->x, p1->y - p2->y);
}

int *func_0202f874(int *p, int arg)
{
    *p = FX_MulFunc(*p, arg);
    *(p + 1) = FX_MulFunc(*(p + 1), arg);
    return p;
}

long long func_0202f838(struct Vec2 *a, struct Vec2 *b)
{
    int diffx, diffy;
    int local[2];
    int c, a2, result1, result2;

    diffx = a->x - b->x;
    diffy = a->y - b->y;
    func_0202f8fc(local, diffx, diffy);

    c = local[1];
    a2 = local[0];
    result1 = FX_MulFunc(a2, a2);
    result2 = FX_MulFunc(c, c);
    return result1 + result2;
}

int func_0202f7f4(int *ptr)
{
    int val;
    int abs;

    val = FX_Sqrt((int) func_0202f838((struct Vec2 *) ptr, (struct Vec2 *) ((unsigned int) data_021c30b8)));
    abs = val < 0 ? -val : val;
    if (abs < 4) {
        return 0;
    }
    *ptr = FX_Div(*ptr, val);
    *(ptr + 1) = FX_Div(*(ptr + 1), val);
    return 1;
}

void func_0202f7cc(unsigned int *param, int a)
{
    unsigned int local[3];
    unsigned int *r4 = param;
    unsigned int tmp0, tmp2;

    tmp0 = r4[0];
    tmp2 = r4[1];
    local[0] = tmp0;
    local[1] = 0;
    local[2] = tmp2;
    func_020ea6e0(local, a);
    r4[0] = local[0];
    r4[1] = local[2];
}

void func_0202f7a0(void *out, void *a, void *b)
{
    int tmp[2];
    func_0202f898((int) tmp, (struct Pair *) b, (struct Pair *) a);
    *(int *) out = -tmp[1];
    *(int *) ((char *) out + 4) = tmp[0];
    func_0202f7f4((int *) out);
}

UnkStruct_0202f740_2 *func_0202f740(UnkStruct_0202f740_2 *self, int a1, int a2)
{
    UnkStruct_0202f740 temp;

    self->unk_00 = (void *) ((char *) data_020da1a4);
    func_0202f8fc((int *) (&self->arr[0]), 0, 0);
    func_0202f8fc((int *) (&self->arr[1]), 0, 0);
    func_0202f8fc((int *) (&self->arr[2]), 0, 0);
    func_0202f8fc((int *) (&temp), 0, 0);
    func_0202f7a0((void *) (&temp), (void *) a1, (void *) a2);
    func_0202f6ac((struct UnkStruct_0202f6ac *) self, a1, a2, (int) (&temp));

    return self;
}

struct UnkStruct_0202f6f4_2 *func_0202f6f4(struct UnkStruct_0202f6f4_2 *self, int a, int b, int c)
{
    self->unk_00 = (unsigned int) data_020da1a4;
    func_0202f8fc((int *) (&self->unk_04), 0, 0);
    func_0202f8fc((int *) (&self->unk_0C), 0, 0);
    func_0202f8fc((int *) (&self->unk_14), 0, 0);
    func_0202f6ac((struct UnkStruct_0202f6ac *) self, a, b, c);
    return self;
}

void func_0202f6e8(void **out)
{
    *out = ((unsigned char *) data_020da1a4);
}

void func_0202f6dc(void **ptr)
{
    *ptr = ((int *) data_020da1a4);
}

void func_0202f6ac(struct UnkStruct_0202f6ac *a, int b, int c, int d)
{
    func_0202f8e4(&a->unk_04, (unsigned int *) b);
    func_0202f8e4(&a->unk_0C, (unsigned int *) c);
    func_0202f8e4(&a->unk_14, (unsigned int *) d);
    a->unk_1C = func_0202f688((UnkStruct_0202f688 *) a);
}

int func_0202f688(UnkStruct_0202f688 *data)
{
    int a;
    int b;
    a = FX_MulFunc(data->unk_14, data->unk_04);
    b = FX_MulFunc(data->unk_18, data->unk_08);
    return -(a + b);
}

int func_0202f660(struct s0 *p0, struct s1 *p1)
{
    int v = p0->unk_1C;
    int a = FX_MulFunc(p0->unk_14, p1->unk_00);
    int b = FX_MulFunc(p0->unk_18, p1->unk_04);
    return (a + b) + v;
}

int func_0202f59c(UnkStruct_0202f59c *s, UnkStruct_0202f59c_2 *out, int p, int q)
{
    UnkStruct_0202f59c b;
    int det;
    int t;
    int u;
    int c1, c2, c3;
    int c0;
    int m;

    func_0202f740((UnkStruct_0202f740_2 *) (&b), p, q);
    det = FX_MulFunc(s->a, b.b) - FX_MulFunc(b.a, s->b);
    if ((det < 0 ? -det : det) < 4) {
        goto plain;
    }
    c1 = b.c;
    c0 = s->c;
    out->y = FX_Div(FX_MulFunc(b.a, c0) - FX_MulFunc(s->a, c1), det);
    t = s->a;
    if ((t < 0 ? -t : t) >= 4) {
        c2 = s->c;
        m = FX_MulFunc(s->b, out->y);
        out->x = FX_Div(-(m + c2), t);
        func_0202f6e8((void **) (&b));
        return 1;
    }
    u = b.a;
    if ((u < 0 ? -u : u) < 4) {
        goto plain;
    }
    c3 = b.c;
    m = FX_MulFunc(b.b, out->y);
    out->x = FX_Div(-(m + c3), u);
    func_0202f6e8((void **) (&b));
    return 1;
plain:
    func_0202f6e8((void **) (&b));
    return 0;
}

int func_0202f520(void *a0, void *a1, void *a2, void *a3)
{
    unsigned char buf[32];
    int tmp1, tmp2, tmp3, tmp4, ret;

    tmp1 = func_0202f660((struct s0 *) a0, (struct s1 *) a2);
    tmp2 = func_0202f660((struct s0 *) a0, (struct s1 *) a3);

    if (FX_MulFunc(tmp1, tmp2) < 0) {
        func_0202f740((UnkStruct_0202f740_2 *) buf, (int) a2, (int) a3);
        tmp3 = func_0202f660((struct s0 *) buf, (struct s1 *) ((char *) a0 + 4));
        tmp4 = func_0202f660((struct s0 *) buf, (struct s1 *) ((char *) a0 + 12));

        if (FX_MulFunc(tmp3, tmp4) < 0) {
            ret = func_0202f59c((UnkStruct_0202f59c *) a0, (UnkStruct_0202f59c_2 *) a1, (int) a2, (int) a3);
            func_0202f6e8((void **) buf);
            return ret;
        }
        func_0202f6e8((void **) buf);
    }
    return 0;
}
