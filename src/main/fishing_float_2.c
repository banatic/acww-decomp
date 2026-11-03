/* fishing_float_2: 21 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206060c @ 0x0206060c, 0x40 bytes, Thumb
 * func_020605d8 @ 0x020605d8, 0x34 bytes, Thumb
 * func_020605ac @ 0x020605ac, 0x2c bytes, Thumb
 * func_02060588 @ 0x02060588, 0x24 bytes, Thumb
 * func_0206053c @ 0x0206053c, 0x4c bytes, Thumb
 * func_0206052c @ 0x0206052c, 0x10 bytes, Thumb
 * func_02060508 @ 0x02060508, 0x24 bytes, Thumb
 * func_02060504 @ 0x02060504, 0x4 bytes, Thumb
 * func_02060500 @ 0x02060500, 0x4 bytes, Thumb
 * func_020604fc @ 0x020604fc, 0x4 bytes, Thumb
 * func_020604f8 @ 0x020604f8, 0x4 bytes, Thumb
 * func_020604e8 @ 0x020604e8, 0x10 bytes, Thumb
 * func_020604c8 @ 0x020604c8, 0x20 bytes, Thumb
 * func_020604b0 @ 0x020604b0, 0x18 bytes, Thumb
 * func_02060480 @ 0x02060480, 0x2e bytes, Thumb
 * func_02060474 @ 0x02060474, 0xc bytes, Thumb
 * func_02060460 @ 0x02060460, 0x14 bytes, Thumb
 * func_02060448 @ 0x02060448, 0x16 bytes, Thumb
 * func_02060438 @ 0x02060438, 0xe bytes, Thumb
 * func_02060428 @ 0x02060428, 0xe bytes, Thumb
 * func_0206026c @ 0x0206026c, 0x1bc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xd];
    unsigned char unk_0D;
} UnkStruct_0206053c;

struct UnkStruct_020604c8 {
    unsigned char pad_00[0x2c];
    int unk_2C;
};

struct UnkStruct_020604b0 {
    char pad_00[0x2c];
    int unk_2C;
};

typedef struct {
    unsigned char pad_00[0x2c];
    int unk_2C;
    unsigned char pad_30[0x0c];
    int unk_3C;
} UnkStruct_02060448;

typedef struct {
    int a, b, c;
} Src;

typedef struct {
    char pad_00[0x1c];
    int a, b, c;
} Dst;

typedef struct UnkStruct_0206026c UnkStruct_0206026c;

typedef struct ObjVtbl {
    int pad_00[23];
    int (*method5C)(UnkStruct_0206026c *, void *);
} ObjVtbl;

struct UnkStruct_0206026c {
    ObjVtbl *vtbl;
};

typedef struct Vec3 {
    int x, y, z;
} Vec3;

typedef struct UnkStruct_0206026c_2 {
    int unk_00;
    int unk_04;
    Vec3 vec;
    int unk_14;
    int unk_18;
    Vec3 unk_1C;
    UnkStruct_0206026c *unk_28;
    int unk_2C;
    int unk_30;
    int unk_34;
} UnkStruct_0206026c_2;

typedef struct UnkStruct_0206026c_3 {
    int pad_00[12];
    int flag;
    int pad_34;
    int pad_38;
    int something;
} UnkStruct_0206026c_3;

extern char *func_020606d4(unsigned char *ctx, int val);
extern int func_02055454(int);
extern unsigned char data_021cad80[];
extern void func_020b9ec4(void *p);
extern void func_020ba004(void *p);
extern int func_02060904(int);
extern int func_020606fc(int, int);
extern int func_020608fc(void);
extern int func_02064af4(int, int, int);
extern int func_021077e8(int);
extern int func_020606f0(int, int);
extern void func_02055b50(int, int);
extern UnkStruct_0206053c *func_020606e4(void *a, int);
extern int func_020b9eec(UnkStruct_0206053c *e, int v, int k);
extern int func_ov003_0222aba4(int a);
extern int func_ov003_0222ab4c(int x);
extern int func_02034270(void *dst, const void *src, int a, int b);
extern void func_0203423c(void *ptr);
extern int func_ov003_0222ab14(int);
extern int func_ov003_0222aae8(unsigned int);
extern int func_ov003_0222a960(int, int);
extern void func_0209129c(int value);
extern int func_020912d4(int kind, int *vec, int a, int b);
extern void func_0205fbc4(int *a, int *b, int *c, int *d, int e);
extern int func_ov003_0222a784(int value);

void func_020605d8(unsigned char *self, int idx);
void func_0206052c(char *base, int index, int value);
int func_02060504(unsigned char *p0);
void func_0206026c(UnkStruct_0206026c_2 *self, int param);

void func_0206060c(char *p)
{
    func_02055454((int) func_020606d4(data_021cad80, func_02060504((unsigned char *) p)));
    func_020605d8(data_021cad80, func_02060504((unsigned char *) p));
    func_0206052c((char *) data_021cad80, func_02060504((unsigned char *) p), 0);
    *p = 9;
}

void func_020605d8(unsigned char *self, int idx)
{
    unsigned int flag;
    unsigned char *p;
    int o;

    o = idx * 28;
    p = self + o + 0xe5;
    flag = (*p == 1);
    if (flag > 0) {
        func_020b9ec4(self + 0xd8 + o);
    } else {
        func_020ba004(self + 0xd8 + o);
    }
}

int func_020605ac(int a, int b, int c)
{
    int r5 = a;
    int r4 = b;
    int r0 = c;
    int r6 = func_02060904(r0);
    int r4_2 = func_020606fc(r5, r4);
    int r2 = func_020608fc();
    return func_02064af4(r6, r4_2, r2);
}

void func_02060588(int a, int b)
{
    int temp;
    temp = func_021077e8(func_020606fc(a, b));
    func_02055b50(func_020606f0(a, b), temp);
}

int func_0206053c(void *a, void *b)
{
    UnkStruct_0206053c *e = func_020606e4(a, (int) b);
    unsigned int k = e->unk_0D;
    unsigned int t1;
    unsigned int t2;
    if (k == 2) {
        t1 = 1;
    } else {
        t1 = 0;
    }
    if (t1 > 0) {
        return 1;
    }
    if (k == 1) {
        t2 = 1;
    } else {
        t2 = 0;
    }
    if (t2 == 0) {
        func_020b9eec(e, func_021077e8((int) ((unsigned int *) (unsigned long) func_020606fc((int) a, (int) b))), 1);
    }
    return 0;
}

void func_0206052c(char *base, int index, int value)
{
    *(int *) (base + index * 4 + 0x750) = value;
}

int func_02060508(int a, int b)
{
    int *p;
    if (b >= 4) {
        return 0;
    }
    p = *(int **) (a + (b << 2) + 0x750);
    if (p != 0 && p[1] == 4) {
        return (int) p;
    }
    return 0;
}

int func_02060504(unsigned char *p0)
{
    return p0[0];
}

void func_02060500(int *p0, int p1)
{
    p0[15] = p1;
}

void func_020604fc(int *p0, int p1)
{
    p0[11] = p1;
}

int func_020604f8(int *p0)
{
    return p0[11];
}

int func_020604e8(void *ptr)
{
    int value;
    value = *(int *) ((char *) ptr + 4);
    value -= 4;
    if ((unsigned int) value > 1) {
        return 0;
    }
    return 1;
}

int func_020604c8(struct UnkStruct_020604c8 *p)
{
    int v = p->unk_2C;
    if (v == 0) {
        func_0206026c((UnkStruct_0206026c_2 *) p, 7);
        return 0;
    }
    return func_ov003_0222aba4(v);
}

int func_020604b0(struct UnkStruct_020604b0 *p)
{
    if (p->unk_2C == 0) {
        return 1;
    }
    return func_ov003_0222ab4c(p->unk_2C);
}

void func_02060480(void *arg)
{
    unsigned char buf[0x40];
    unsigned int *p;
    unsigned int v;

    func_02034270(buf, (char *) arg + 8, 1, 1);
    p = (unsigned int *) (buf + 0x30);
    if (*p != 0) {
        v = *(unsigned int *) (buf + 0x3c);
        *(unsigned int *) ((char *) arg + 0xc) = v + 0xcd;
    }
    func_0203423c(buf);
}

int func_02060474(int *p0)
{
    return func_ov003_0222ab14(p0[11]);
}

void func_02060460(void *param)
{
    unsigned int val = *(unsigned int *) ((char *) param + 0x2c);
    func_ov003_0222aae8(val);
    *(unsigned int *) ((char *) param + 0x2c) = 0;
}

void func_02060448(UnkStruct_02060448 *s)
{
    func_ov003_0222a960(s->unk_3C, 0);
    s->unk_2C = 0;
}

void func_02060438(Dst *d, Src *s)
{
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
}

void func_02060428(unsigned int *dest, const unsigned int *src)
{
    dest[2] = src[0];
    dest[3] = src[1];
    dest[4] = src[2];
}

void func_0206026c(UnkStruct_0206026c_2 *self, int param)
{
    int old;
    int vec0[3];
    UnkStruct_0206026c_3 tmp;
    int vecA7[3];
    int vecB7[3];
    int vecA8[3];
    int vecB8[3];

    if (self->unk_34 != -1) {
        func_0209129c(self->unk_34);
        self->unk_34 = -1;
    }
    if (self->unk_28 == (UnkStruct_0206026c *) 0) {
        self->unk_04 = 0;
        goto end;
    }
    old = self->unk_04;
    self->unk_04 = param;
    self->unk_30 = 0;
    func_02034270(&tmp, (const void *) (&self->vec), 1, 1);

    switch (param) {
        case 1:
            if (self->unk_2C != 0 && func_ov003_0222a784(self->unk_2C) != 0) {
                self->unk_2C = 0;
            }
            break;
        case 7:
            if (self->unk_28->vtbl->method5C(self->unk_28, &self->unk_1C) == 0) {
                Vec3 *src = (Vec3 *) ((char *) self->unk_28 + 0x5c);
                self->unk_1C.x = src->x;
                self->unk_1C.y = src->y;
                self->unk_1C.z = src->z;
            }
            vecA7[0] = self->unk_1C.x;
            vecA7[1] = self->unk_1C.y;
            vecA7[2] = self->unk_1C.z;
            vecB7[0] = self->vec.x;
            vecB7[1] = self->vec.y;
            vecB7[2] = self->vec.z;
            func_0205fbc4(vecA7, vecB7, &self->unk_14, &self->unk_18, 1);
            if (tmp.flag != 0) {
                vec0[0] = self->vec.x;
                vec0[1] = self->vec.y;
                vec0[2] = self->vec.z;
                vec0[1] = tmp.something;
                func_020912d4(0xd, vec0, 0, 0);
            }
            break;
        case 8:
            if (self->unk_28->vtbl->method5C(self->unk_28, &self->unk_1C) == 0) {
                Vec3 *src = (Vec3 *) ((char *) self->unk_28 + 0x5c);
                self->unk_1C.x = src->x;
                self->unk_1C.y = src->y;
                self->unk_1C.z = src->z;
            }
            vecA8[0] = self->unk_1C.x;
            vecA8[1] = self->unk_1C.y;
            vecA8[2] = self->unk_1C.z;
            vecB8[0] = self->vec.x;
            vecB8[1] = self->vec.y;
            vecB8[2] = self->vec.z;
            func_0205fbc4(vecA8, vecB8, &self->unk_14, &self->unk_18, 2);
            break;
        case 5:
            if (tmp.flag != 0) {
                vec0[0] = self->vec.x;
                vec0[1] = self->vec.y;
                vec0[2] = self->vec.z;
                vec0[1] = tmp.something;
                func_020912d4(0x10, vec0, 0, 0);
            }
            break;
        case 4:
            if (old == 6) {
                if (tmp.flag != 0) {
                    vec0[0] = self->vec.x;
                    vec0[1] = self->vec.y;
                    vec0[2] = self->vec.z;
                    vec0[1] = tmp.something;
                    func_020912d4(0xf, vec0, 0, 0);
                }
            }
            break;
        case 6:
            if (tmp.flag != 0) {
                vec0[0] = self->vec.x;
                vec0[1] = self->vec.y;
                vec0[2] = self->vec.z;
                vec0[1] = tmp.something;
                self->unk_34 = func_020912d4(0x11, vec0, 0, 0);
            }
            break;
        default:
            break;
    }

    func_0203423c(&tmp);
end:
    return;
}
