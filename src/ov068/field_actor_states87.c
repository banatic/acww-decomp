/* field_actor_states87: 16 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0227207c @ 0x0227207c, 0x38 bytes, Thumb
 * func_ov068_02272044 @ 0x02272044, 0x38 bytes, Thumb
 * func_ov068_0227200c @ 0x0227200c, 0x36 bytes, Thumb
 * func_ov068_02271f80 @ 0x02271f80, 0x8c bytes, Thumb
 * func_ov068_02271f7c @ 0x02271f7c, 0x2 bytes, Thumb
 * func_ov068_02271f50 @ 0x02271f50, 0x2c bytes, Thumb
 * func_ov068_02271f28 @ 0x02271f28, 0x28 bytes, Thumb
 * func_ov068_02271ee4 @ 0x02271ee4, 0x44 bytes, Thumb
 * func_ov068_02271ed0 @ 0x02271ed0, 0x14 bytes, Thumb
 * func_ov068_02271e98 @ 0x02271e98, 0x36 bytes, Thumb
 * func_ov068_02271e7c @ 0x02271e7c, 0x1a bytes, Thumb
 * func_ov068_02271e78 @ 0x02271e78, 0x2 bytes, Thumb
 * func_ov068_02271e4c @ 0x02271e4c, 0x2c bytes, Thumb
 * func_ov068_02271e24 @ 0x02271e24, 0x28 bytes, Thumb
 * func_ov068_02271de8 @ 0x02271de8, 0x3c bytes, Thumb
 * func_ov068_02271dd4 @ 0x02271dd4, 0x14 bytes, Thumb
 */

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
} UnkStruct_0227207c;

struct UnkStruct_02271f50 {
    unsigned char pad_00[0x5c];
    int a;
    unsigned char pad_60[4];
    int b;
    unsigned char pad_68[0x26];
    short s;
};

struct UnkStruct_02271de8 {
    char pad_00[0x2d0];
    void *unk_2D0;
    char pad_2D4[0x51c];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
};

extern void *func_02096718(int);
extern int func_02008258(void *, int);
extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);
extern void func_020109a0(void *p, int b, int c, unsigned short d);
extern void func_0200f268(char *, int);
extern int func_02011368(void *p);
extern void func_0209e474(unsigned int *p);
extern void func_0209e140(unsigned int *p, int x);
extern void func_0200f7ac(void *p, int v, void *st);
extern void func_02010f5c(int argument0);
extern int func_02056f28(void *ptr, int value);
extern void func_0200f888(void *ptr);
extern int func_02056f94(void *);
extern int func_0200c3b0(void *, int, int, int);
extern unsigned char *func_0209626c(void);
extern int func_0200d554(void *self, int a, int b);

void *func_ov068_0227200c(void *a, void *b, void *c);
unsigned int func_ov068_02271e98(unsigned int a, unsigned int b, unsigned int c);

void *func_ov068_0227207c(void)
{
    UnkStruct_0227207c *p = func_02096718(4);
    if (p) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        return func_ov068_0227200c(p, (void *) 6, (void *) (-1));
    } else {
        return 0;
    }
}

int func_ov068_02272044(void)
{
    void *p = func_02096718(4);
    if (p) {
        *(int *) ((char *) p + 0x7fc) = func_02008258(p, *(int *) ((char *) p + 0x7f0));
        return (int) func_ov068_02271e98((unsigned int) p, 6, -1);
    } else {
        return 0;
    }
}

void *func_ov068_0227200c(void *a, void *b, void *c)
{
    char buf[0x20];
    void *ret;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x87, b, c);
    ret = func_0200e894(a, buf);
    func_0200e91c(buf);
    return ret;
}

void func_ov068_02271f80(void *p, void *message, int previous)
{
    struct {
        unsigned short flags;
        unsigned short pad;
        unsigned int a;
        unsigned int b;
    } st;
    int val;

    func_020109a0(p, 0x82, 0, 0);
    *((unsigned short *) ((char *) p + 0x8e)) = 0;
    func_0200f268(p, 0);
    val = func_02011368(p);
    if (val != 0) {
        st.a = 0;
        st.b = 0;
        func_0209e474(&st.a);
        func_0209e140(&st.a, 1);
        st.flags = (st.flags & ~0x7f) | (((unsigned char *) &st)[9] & 0x7f);
        st.flags = (st.flags & 0xfffff87f) | ((((unsigned char *) &st)[8] & 0xf) << 7);
        st.flags = (st.flags & 0xffff07ff) | ((((unsigned char *) &st)[7] & 0x1f) << 0xb);
        func_0200f7ac(p, val, &st);
    }
}

void func_ov068_02271f7c(void *receiver, int event) {}

void func_ov068_02271f50(struct UnkStruct_02271f50 *p)
{
    p->a += 0x1c00;
    p->b -= 0x2c00;
    p->s += 0x8000;
}

void func_ov068_02271f28(void *param)
{
    void *r4 = param;
    func_02010f5c((int) param);
    if (func_02056f28((char *) r4 + 0x2d0, 0x16)) {
        func_0200f888(r4);
    }
}

void func_ov068_02271ee4(void *self)
{
    unsigned char *flag;
    if (func_02056f94((char *) self + 0x2d0)) {
        *(int *) ((char *) self + 0x7fc) = func_02008258(self, *(int *) ((char *) self + 0x7f0));
        func_0200c3b0(self, 0, 5, -1);
        flag = func_0209626c();
        *flag = 0;
    }
}

void func_ov068_02271ed0(void *p)
{
    func_ov068_02271f28(p);
    func_ov068_02271ee4(p);
}

unsigned int func_ov068_02271e98(unsigned int a, unsigned int b, unsigned int c)
{
    unsigned char local[0x20];
    unsigned int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x88, (void *) b, (void *) c);
    result = (unsigned int) func_0200e894((void *) a, local);
    func_0200e91c(local);
    return result;
}

void func_ov068_02271e7c(void *p, void *message, int previous)
{
    func_020109a0(p, 0x83, 3, 0);
    *(unsigned short *) ((unsigned char *) p + 0x8e) = 0;
}

void func_ov068_02271e78(void *receiver, int event) {}

void func_ov068_02271e4c(void *r0)
{
    int r1;
    int r2;
    short *r0_short;

    r2 = *(int *) ((char *) r0 + 0x5c);
    r1 = r2 - 0x1c00;
    *(int *) ((char *) r0 + 0x5c) = r1;

    r2 = *(int *) ((char *) r0 + 0x64);
    r1 = r2 + 0x2c00;
    *(int *) ((char *) r0 + 0x64) = r1;

    r1 = 0x8e;
    r2 = *(short *) ((char *) r0 + r1);
    r1 = r2 + 0x8000;
    r0_short = (short *) ((char *) r0 + 0x8e);
    *r0_short = (short) r1;
}

void func_ov068_02271e24(void *param)
{
    void *r4 = param;
    func_02010f5c((int) param);
    if (func_02056f28((char *) r4 + 0x2d0, 8) != 0) {
        func_0200f888(r4);
    }
}

void func_ov068_02271de8(struct UnkStruct_02271de8 *self)
{
    if (func_02056f94(&self->unk_2D0) != 0) {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
        func_0200d554(self, 9, -1);
    }
}

void func_ov068_02271dd4(void *arg)
{
    func_ov068_02271e24(arg);
    func_ov068_02271de8((struct UnkStruct_02271de8 *) arg);
}
