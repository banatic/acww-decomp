/* field_actor_room_states_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02227d7c @ 0x02227d7c, 0x2 bytes, Thumb
 * func_ov004_02227d60 @ 0x02227d60, 0x1c bytes, Thumb
 * func_ov004_02227cb0 @ 0x02227cb0, 0xb0 bytes, Thumb
 * func_ov004_02227bf4 @ 0x02227bf4, 0xbc bytes, Thumb
 */

struct UnkStruct_02227cb0 {
    int a;
    int b;
    int c;
};

typedef struct {
    int x, y, z;
} Vec3;

extern void func_0200fbc4(char *self, int a, int b, int c);
extern void func_02010f5c(void *self);
extern void func_020eaca0(struct UnkStruct_02227cb0 *out, struct UnkStruct_02227cb0 *a, struct UnkStruct_02227cb0 *b);
extern int func_020ea9c8(struct UnkStruct_02227cb0 *v);
extern int FX_MulFunc(int a, int b);
extern void func_0200f95c(void *self);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02056f28(void *p, int k);
extern void func_0200f888(void *self);
extern void *func_02032c64(void *);
extern void *func_02032c50(void *);
extern int func_020082a0(void *, int);
extern void func_02031288(void *, void *, void *, int, int, void *, int);
extern int func_020310c8(int value);
extern int func_020ea990(Vec3 *, void *);
extern int FX_Div(int numerator, int denominator);

void func_ov004_02227d7c(void *callbackObject, int event) {}

void func_ov004_02227d60(char *self)
{
    char *p = self + 0x7d4;
    func_0200fbc4(self, *(int *) (p + 8), *(int *) (p + 0xc), *(short *) (p + 4));
}

void func_ov004_02227cb0(unsigned char *self)
{
    struct UnkStruct_02227cb0 v;
    int s, t;
    func_02010f5c(self);
    s = *(int *) (self + 0x704);
    if (s == 1) {
        func_020eaca0(&v, (struct UnkStruct_02227cb0 *) (self + 0x5c), (struct UnkStruct_02227cb0 *) (self + 0x68));
        t = FX_MulFunc(func_020ea9c8(&v), 0x3ae1) << 2;
        if (t <= *(int *) (self + 0x2d4)) {
            *(int *) (self + 0x2e0) = t;
        }
        func_0200f95c(self);
        if (t == 0) {
            func_020109fc(self, 0, 3, 0);
        }
    } else if (s != 0) {
        if (func_02056f28(self + 0x2d0, 1) != 0 || func_02056f28(self + 0x2d0, 6) != 0 ||
            func_02056f28(self + 0x2d0, 0xb) != 0 || func_02056f28(self + 0x2d0, 0x10) != 0) {
            func_0200f888(self);
        }
    }
}

void func_ov004_02227bf4(char *self)
{
    char buf[0x30];
    Vec3 v;
    char *o;
    short a;
    void *p;
    int st;
    o = self + 0x5c;
    func_02032c64(buf);
    a = *(short *) (self + 0x8e);
    if (func_020082a0(self, *(int *) (self + 0x7f0)) == 0) {
        p = buf;
    } else {
        p = self + 0x7a4;
    }
    func_02031288(p, o, self + 0x68, a, 0xfd7, self, 0xf);
    func_02032c50(buf);
    *(int *) (o + 4) = func_020310c8(0);
    {
        char *b = self + 0x7d4;
        st = *(int *) b;
        if ((unsigned) (st - 1) <= 1) {
            int z = *(int *) (b + 0xc);
            int y = *(int *) (o + 4);
            int x = *(int *) (b + 8);
            v.x = x;
            v.y = y;
            v.z = z;
            if (func_020ea990(&v, o) < 0x1000) {
                int t = 6 * FX_Div(0x1000 - func_020ea990(&v, o), 0x1000);
                if (st == 1) {
                    *(int *) (o + 4) = *(int *) (o + 4) + (t >> 5);
                } else {
                    *(int *) (o + 4) = *(int *) (o + 4) - (t >> 5);
                }
            }
        }
    }
}
