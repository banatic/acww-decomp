/* snowball_spawner: 10 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0223654c @ 0x0223654c, 0x18 bytes, Thumb
 * func_ov003_0223652c @ 0x0223652c, 0x20 bytes, Thumb
 * func_ov003_0223650c @ 0x0223650c, 0x20 bytes, Thumb
 * func_ov003_022364e4 @ 0x022364e4, 0x28 bytes, Thumb
 * func_ov003_022364cc @ 0x022364cc, 0x16 bytes, Thumb
 * func_ov003_022364c8 @ 0x022364c8, 0x4 bytes, Thumb
 * func_ov003_022364c4 @ 0x022364c4, 0x4 bytes, Thumb
 * func_ov003_022364c0 @ 0x022364c0, 0x4 bytes, Thumb
 * func_ov003_02236374 @ 0x02236374, 0x14c bytes, Thumb
 * func_ov003_02236274 @ 0x02236274, 0x100 bytes, Thumb
 */

typedef struct {
    volatile int v;
} UnkStruct_0223652c;

typedef struct {
    volatile int v;
} UnkStruct_0223650c;

typedef struct {
    volatile int v;
} UnkStruct_022364e4;

typedef struct {
    char pad[0x64];
    int unk_64;
} UnkStruct_02236374;

typedef struct {
    unsigned char sec;
    unsigned char min;
    unsigned char hour;
    unsigned char day;
    unsigned char mon;
    unsigned char year;
    unsigned short pad;
} DateTime;

typedef union {
    DateTime t;
    unsigned int w[2];
} DateTimeU;

typedef struct {
    int x, y, z, w;
} Vec4;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    void *cells;
    unsigned int w;
    unsigned int h;
} Grid;

extern void *func_020edf70(unsigned int size);
extern void *func_020ee660(void *obj);
extern unsigned char data_020da13c[];
extern unsigned char data_ov003_0223c550[];
extern void func_020ee62c(void *obj);
extern void func_020edf54(void *obj);
extern UnkStruct_02236374 *data_020ccf94;
extern int func_02073dd4(UnkStruct_02236374 *p, int val);
extern int func_020b6598(void);
extern Vec4 *func_020b03f8(void);
extern void func_020b0518(Vec4 *p);
extern void func_0209e474(DateTime *d);
extern void func_0209e140(DateTime *d, int n);
extern int func_020b0594(char *base, unsigned int index, int *o1, int *o2, int *o3, unsigned char *o4, unsigned char *o5,
                         unsigned char *o6);
extern int func_020b6660(void);
extern int func_020b0568(char *base);
extern int func_ov003_02235d88(void *self, void *dst, void *ref, int f);
extern int func_02003348(int chan, int slot, void *arg, int d, void *self);
extern unsigned char data_021f3b56[];
extern __arm int func_02037e0c(void *acre, int x, int z, int w);
extern int func_02037e44(void *acre, unsigned short *v, int x, int z, int w);
extern int func_0204bb54(int it);
extern int func_0204bb2c(int it);
extern void func_0204f7ac(void *out, unsigned int ax, unsigned int ay, int x, int z);
extern unsigned char data_021c80bc[];

UnkStruct_0223652c *func_ov003_0223652c(UnkStruct_0223652c *obj);
void func_ov003_02236374(void *self);
void func_ov003_02236274(void *self);

void *func_ov003_0223654c(void)
{
    void *p;
    p = func_020edf70(0x50);
    if (p) {
        p = (void *) func_ov003_0223652c((UnkStruct_0223652c *) p);
    }
    return p;
}

UnkStruct_0223652c *func_ov003_0223652c(UnkStruct_0223652c *obj)
{
    func_020ee660(obj);
    obj->v = (unsigned int) data_020da13c;
    obj->v = (unsigned int) data_ov003_0223c550;
    return obj;
}

UnkStruct_0223650c *func_ov003_0223650c(UnkStruct_0223650c *obj)
{
    obj->v = (unsigned int) data_ov003_0223c550;
    obj->v = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}

UnkStruct_022364e4 *func_ov003_022364e4(UnkStruct_022364e4 *obj)
{
    obj->v = (unsigned int) data_ov003_0223c550;
    obj->v = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    func_020edf54(obj);
    return obj;
}

int func_ov003_022364cc(void *self)
{
    func_ov003_02236274(self);
    func_ov003_02236374(self);
    return 1;
}

int func_ov003_022364c8(void)
{
    return 1;
}

int func_ov003_022364c4(void)
{
    return 1;
}

int func_ov003_022364c0(void)
{
    return 1;
}

void func_ov003_02236374(void *self)
{
    unsigned char yy;
    unsigned char mm;
    unsigned char dd;
    DateTimeU now;
    int o1;
    int o2;
    int o3;
    Vec3 a;
    Vec3 b;
    unsigned int i;
    Vec4 *p;
    Vec4 *q;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 || func_020b6598() == 0) {
        func_020b0518(func_020b03f8());
        return;
    }

    for (i = 0; i < 3; i++) {
        now.w[0] = 0;
        now.w[1] = 0;
        func_0209e474(&now.t);
        if (now.t.hour < 6) {
            func_0209e140(&now.t, 1);
        }
        if (func_020b0594((char *) data_021f3b56, i, &o1, &o2, &o3, &yy, &mm, &dd) == 0) {
            continue;
        }
        if (yy != now.t.year) {
            continue;
        }
        if (mm != now.t.mon) {
            continue;
        }
        if (dd != now.t.day) {
            continue;
        }
        func_020b0518(func_020b03f8());
        return;
    }

    if (func_020b6660() == 0) {
        return;
    }
    if (func_020b0568((char *) data_021f3b56) != 0) {
        return;
    }

    if (func_020b03f8()->x != 0) {
        p = func_020b03f8();
        a.x = p->x;
        a.y = p->y;
        a.z = p->z;
    } else {
        func_ov003_02235d88(self, &a, 0, 1);
    }

    if (func_020b03f8()[1].x != 0) {
        p = func_020b03f8();
        q = &p[1];
        b.x = q->x;
        b.y = q->y;
        b.z = q->z;
    } else {
        func_ov003_02235d88(self, &b, &a, 1);
    }

    if (func_02003348(0xbd, 0, &a, 0, self) != 0) {
        p = func_020b03f8();
        p->x = a.x;
        p->y = a.y;
        p->z = a.z;
    }
    if (func_02003348(0xbd, 1, &b, 0, self) != 0) {
        p = func_020b03f8();
        p[1].x = b.x;
        p[1].y = b.y;
        p[1].z = b.z;
    }
}

void func_ov003_02236274(void *self)
{
    Grid *g;
    unsigned int ay, ax;
    int i, j;
    int n;
    void *acre;
    int it;
    int idx;
    unsigned short tmp;
    Vec3 out;

    g = *(Grid **) data_021c80bc;
    for (ay = 1; ay <= 4; ay++) {
        for (ax = 1; ax <= 4; ax++) {
            if (ax < g->w && ay < g->h && g->cells != 0) {
                acre = (char *) g->cells + (ax + ay * g->w) * 0x28;
            } else {
                acre = 0;
            }
            if (acre == 0) {
                continue;
            }
            for (i = 0; i < 0x10; i++) {
                for (j = 0; j < 0x10; j++) {
                    it = func_02037e0c(acre, j, i, 0);
                    if (it == 0) {
                        continue;
                    }
                    if (func_0204bb54(it) == 0) {
                        continue;
                    }
                    idx = func_0204bb2c(it);
                    if (func_020b0594((char *) data_021f3b56, idx, 0, 0, 0, 0, 0, 0) == 0) {
                        tmp = 0xfff1;
                        func_02037e44(acre, &tmp, j, i, 0);
                        continue;
                    }
                    n = idx * 2 + 2;
                    func_0204f7ac(&out, ax, ay, j, i);
                    func_02003348(0xbd, n, &out, 0, self);
                    func_02003348(0xbd, n + 1, &out, 0, self);
                }
            }
        }
    }
}
