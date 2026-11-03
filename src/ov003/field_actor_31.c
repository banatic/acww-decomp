/* field_actor_31: 9 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0221320c @ 0x0221320c, 0xb0 bytes, Thumb
 * func_ov003_022131c8 @ 0x022131c8, 0x42 bytes, Thumb
 * func_ov003_022131a8 @ 0x022131a8, 0x20 bytes, Thumb
 * func_ov003_022131a4 @ 0x022131a4, 0x4 bytes, Thumb
 * func_ov003_02213198 @ 0x02213198, 0xc bytes, Thumb
 * func_ov003_02213178 @ 0x02213178, 0x20 bytes, Thumb
 * func_ov003_02213174 @ 0x02213174, 0x4 bytes, Thumb
 * func_ov003_02213168 @ 0x02213168, 0xc bytes, Thumb
 * func_ov003_02213114 @ 0x02213114, 0x54 bytes, Thumb
 */

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int w[12];
} Mtx;

typedef struct {
    char pad_00[0xc4];
    Vec3 v;
    short d0;
    char pad_D2[0x298 - 0xd2];
    Mtx a;
    char pad_2C8[0x698 - 0x2c8];
    Mtx b;
} UnkStruct_0221320c;

extern void func_02010f5c(void *self);
extern void func_0200ee40(void *self);
extern int func_0200f554(void *self);
extern void func_02010d64(void *self);
extern void func_ov003_022132bc(void *self);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern int func_0200e91c(void *);
extern void func_02077910(int a, int argument1);
extern int func_020778f8(int a);
extern void func_020109a0(void *a, int b, int c, unsigned short d);
extern void func_0205eae0(void *a, int b, int c, int d);
extern int func_0200f328(void *a, int b);

void func_ov003_022131a4(unsigned char *p0, int p1);
void func_ov003_02213198(int a, int argument1);
int func_ov003_02213174(unsigned char *p0);
int func_ov003_02213168(int a);

void func_ov003_0221320c(UnkStruct_0221320c *self)
{
    Vec3 *p;
    volatile Vec3 sv;
    short d;
    Mtx sa, sb;

    func_02010f5c(self);
    p = &self->v;
    sv.x = self->v.x;
    sv.y = p->y;
    sv.z = p->z;
    d = self->d0;
    sa = self->a;
    sb = self->b;
    func_0200ee40(self);
    func_0200f554(self);
    func_02010d64(self);
    func_ov003_022132bc(self);
    self->v.x = sv.x;
    self->v.y = sv.y;
    self->v.z = sv.z;
    self->d0 = d;
    self->a = sa;
    self->b = sb;
}

int func_ov003_022131c8(int a, char b, char c, int d, short e)
{
    char buf[0x1c];
    int result;
    char *p;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x58, d, e);
    p = &buf[0xc];
    p[0] = b;
    p[1] = c;
    result = func_0200e894(a, buf);
    func_0200e91c(buf);
    return result;
}

void func_ov003_022131a8(void *p, unsigned char c, int x, int y)
{
    *(unsigned char *) p = c;
    func_ov003_022131a4((unsigned char *) p, x);
    func_ov003_02213198((int) p, y);
}

void func_ov003_022131a4(unsigned char *p0, int p1)
{
    p0[1] = p1;
}

void func_ov003_02213198(int a, int argument1)
{
    func_02077910(a + 2, argument1);
}

void func_ov003_02213178(unsigned char *src, unsigned char *dst1, unsigned char *dst2, unsigned short *dst3)
{
    *dst1 = *src;
    *dst2 = (unsigned char) func_ov003_02213174((unsigned char *) src);
    *dst3 = (unsigned short) func_ov003_02213168((int) src);
}

int func_ov003_02213174(unsigned char *p0)
{
    return p0[1];
}

int func_ov003_02213168(int a)
{
    return func_020778f8(a + 2);
}

void func_ov003_02213114(void *self, void *data, int previous)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    unsigned char *dst = (unsigned char *) self + 0x7d4;
    unsigned char b0 = p[0];
    unsigned char b1 = p[1];

    dst[0] = b0;
    dst[1] = b1;

    func_ov003_022131a8((unsigned char *) self + 0x8f0, b0, (unsigned char) b1, 0);
    func_020109a0(self, 0x5d, 3, 0);
    func_0205eae0((unsigned char *) self + 0x5a0, 6, 3, 1);
    func_0200f328(self, 0x4f);
}
