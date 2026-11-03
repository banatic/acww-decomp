/* field_actor_32: 11 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02213d18 @ 0x02213d18, 0x88 bytes, Thumb
 * func_ov003_02213cd0 @ 0x02213cd0, 0x48 bytes, Thumb
 * func_ov003_02213bf0 @ 0x02213bf0, 0xe0 bytes, Thumb
 * func_ov003_02213b28 @ 0x02213b28, 0xc8 bytes, Thumb
 * func_ov003_02213ae4 @ 0x02213ae4, 0x44 bytes, Thumb
 * func_ov003_02213ac4 @ 0x02213ac4, 0x20 bytes, Thumb
 * func_ov003_02213ac0 @ 0x02213ac0, 0x4 bytes, Thumb
 * func_ov003_02213ab4 @ 0x02213ab4, 0xc bytes, Thumb
 * func_ov003_02213a90 @ 0x02213a90, 0x22 bytes, Thumb
 * func_ov003_02213a8c @ 0x02213a8c, 0x4 bytes, Thumb
 * func_ov003_02213a80 @ 0x02213a80, 0xc bytes, Thumb
 */

typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

typedef struct UnkStruct_02213d18 {
    char pad_00[0x2d8];
    unsigned int unk_2D8;
    char pad_2DC[4];
    unsigned int unk_2E0;
    char pad_2E4[0x68c - 0x2e0 - 4];
    int unk_68C;
    int unk_690;
    int unk_694;
} UnkStruct_02213d18;

typedef struct {
    int x;
    int y;
    int z;
} Vec3_02213b28;

typedef struct {
    int pad_00;
    int pad_04;
    Vec3_02213b28 vec;
} DstStruct;

typedef struct {
    unsigned char unk_00[0xc];
    unsigned char data[3];
    unsigned char rest[0x11];
} Buffer;

extern int func_ov003_02213ec0(UnkStruct_02213d18 *self);
extern int func_0203f7d0(Vec3 *dst, Vec3 *src);
extern void func_ov003_02214200(UnkStruct_02213d18 *self, Vec3 *in, Vec3 *out1, Vec3 *out2);
extern int func_ov003_02213da0(UnkStruct_02213d18 *self, Vec3 *in, Vec3 *out1, Vec3 *out2);
extern int func_020113a4(int a, int b, int c);
extern void func_0201107c(void *a, int *b);
extern int func_020912d4(int a, void *b, void *c, int d);
extern int func_02056f94(const void *);
extern void *func_0205e8e4(const void *);
extern unsigned char func_ov003_0222e538(int v, unsigned char unused);
extern int func_ov003_0222e5fc(int);
extern unsigned int func_02008258(const void *, unsigned int);
extern int func_02073908(const void *, unsigned int);
extern int func_0200d4e8(const void *, int, int, int);
extern void *data_020ccf94;
extern void func_ov003_022145a0(void *);
extern void func_ov003_02214384(void *);
extern void func_ov003_022145b0(void *);
extern int func_0201100c(void *);
extern void func_02010d64(void *);
extern void func_ov003_02214568(void *);
extern int func_0200f554(void *);
extern unsigned int func_0200e92c(Buffer *buf);
extern void func_0200e90c(Buffer *buf, int a, unsigned int b, signed short c);
extern void *func_0200e894(void *obj, Buffer *buf);
extern int func_0200e91c(Buffer *buf);
extern void func_02077910(int, int argument1);
extern int func_020778f8(int a);

void *func_ov003_02213ae4(void *obj, unsigned char b, unsigned char c, unsigned char d, unsigned int e, signed short f);
void func_ov003_02213ab4(int p0, int argument1);
int func_ov003_02213a80(int a);

void func_ov003_02213d18(UnkStruct_02213d18 *self)
{
    int x0, y0, z0;
    Vec3 v0, v1, out1, out2, v2;

    if (self->unk_2E0 == 0) {
        return;
    }
    if (((self->unk_2D8 << 4) >> 16) < 3) {
        return;
    }
    if (func_ov003_02213ec0(self) != 0) {
        return;
    }

    z0 = self->unk_694;
    y0 = self->unk_690;
    x0 = self->unk_68C;
    v0.x = x0;
    v0.y = y0;
    v0.z = z0;

    func_0203f7d0(&v0, &v0);

    v1.x = v0.x;
    v1.y = v0.y;
    v1.z = v0.z;

    func_ov003_02214200(self, &v1, &out1, &out2);

    v2.x = v0.x;
    v2.y = v0.y;
    v2.z = v0.z;

    func_ov003_02213da0(self, &v2, &out1, &out2);
}

void func_ov003_02213cd0(void *ptr)
{
    int local;
    if (*(int *) ((char *) ptr + 0x98) == 0) {
        return;
    }
    local = func_020113a4(*(int *) ((char *) ptr + 0x98), 0, 0x171);
    func_0201107c(ptr, &local);
    if (*(int *) ((char *) ptr + 0x98) != 0) {
        return;
    }
    func_020912d4(0x2b, (char *) ptr + 0x5c, (char *) ptr + 0x8e, 0);
}

void func_ov003_02213bf0(char *self)
{
    unsigned char *p;
    unsigned char v, t;
    int r;

    if (func_02056f94(self + 0x2d0) == 0 && *(unsigned int *) (self + 0x2e0) != 0) {
        return;
    }

    p = (unsigned char *) (self + 0x7d4);
    if (*p != 0) {
        v = *(p + 4);
        if (v == 0xff) {
            func_ov003_02213ae4((void *) self, 0, v, 0x30, 6, -1);
        } else {
            r = func_ov003_0222e538(v, (unsigned char) *(unsigned int *) (self + 0x800));
            if (r == 0) {
                t = (unsigned char) func_ov003_0222e5fc(v);
                func_ov003_02213ae4((void *) self, 0, v, t, 6, -1);
            } else if (r == 1) {
                *p = 0;
            }
        }
    } else {
        if (func_02056f94((char *) func_0205e8e4(self + 0x5a0) + 0x9c) != 0) {
            *(unsigned int *) (self + 0x7fc) = func_02008258(self, *(unsigned int *) (self + 0x7f0));
            if (func_02073908(data_020ccf94, *(unsigned int *) (self + 0x800)) != 0) {
                func_0200d4e8(self, 9, 1, -1);
            }
        }
    }
}

void func_ov003_02213b28(unsigned char *self)
{
    Vec3_02213b28 tmp, src;
    DstStruct *dst;
    int tx, ty, tz;

    if (func_02073908((const void *) ((*(int *) &data_020ccf94)), *(int *) (self + 0x800)) != 0) {
        func_ov003_022145a0(self);
        func_ov003_02214384(self);
        func_ov003_022145b0(self);
        func_0201100c(self);
        func_02010d64(self);
        func_ov003_02213cd0(self);
        func_ov003_02213bf0((char *) self);
        func_ov003_02214568(self);
    } else {
        func_ov003_02213d18((UnkStruct_02213d18 *) self);
        func_ov003_022145b0(self);
        if (func_0200f554(self) != 0) {
            func_0201100c(self);
        }
        func_02010d64(self);
        func_ov003_02213cd0(self);
        func_ov003_02213bf0((char *) self);
        func_ov003_02214568(self);
    }

    dst = (DstStruct *) (self + 0x7d4);
    tz = *(int *) (self + 0x634);
    ty = *(int *) (self + 0x630);
    tx = *(int *) (self + 0x62c);
    src.x = tx;
    src.y = ty;
    src.z = tz;
    func_0203f7d0((Vec3 *) (&tmp), (Vec3 *) (&src));
    dst->vec.x = tmp.x;
    dst->vec.y = tmp.y;
    dst->vec.z = tmp.z;
}

void *func_ov003_02213ae4(void *obj, unsigned char b, unsigned char c, unsigned char d, unsigned int e, signed short f)
{
    Buffer buf;
    void *ret;

    func_0200e92c(&buf);
    func_0200e90c(&buf, 0x57, e, f);
    {
        unsigned char *p = buf.data;
        p[2] = b;
        p[0] = c;
        p[1] = d;
    }
    ret = func_0200e894(obj, &buf);
    func_0200e91c(&buf);
    return ret;
}

void func_ov003_02213ac4(unsigned char *p, unsigned char a, unsigned char b, unsigned char c, unsigned char d, short e)
{
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
    func_ov003_02213ab4((int) p, (short) e);
}

void func_ov003_02213ac0(unsigned char *p0, int p1)
{
    p0[0] = p1;
}

void func_ov003_02213ab4(int p0, int argument1)
{
    func_02077910((p0 + 4), argument1);
}

void func_ov003_02213a90(unsigned char *src, unsigned char *d0, unsigned char *d1, unsigned char *d2, unsigned char *d3,
                         unsigned short *res)
{
    unsigned char b3;
    *d0 = src[0];
    *d1 = src[1];
    *d2 = src[2];
    b3 = src[3];
    *d3 = b3;
    *res = (unsigned short) func_ov003_02213a80((int) src);
}

int func_ov003_02213a8c(unsigned char *p0)
{
    return p0[0];
}

int func_ov003_02213a80(int a)
{
    return func_020778f8(a + 4);
}
