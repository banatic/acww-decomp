/* pockets_box_scene: 22 functions, module ov100
 * mwccarm 1.2/base -O4,s
 * func_ov100_0229dbf8 @ 0x0229dbf8, 0x40 bytes, Thumb
 * func_ov100_0229dbd0 @ 0x0229dbd0, 0x28 bytes, Thumb
 * func_ov100_0229dba0 @ 0x0229dba0, 0x30 bytes, Thumb
 * func_ov100_0229db70 @ 0x0229db70, 0x30 bytes, Thumb
 * func_ov100_0229db18 @ 0x0229db18, 0x58 bytes, Thumb
 * func_ov100_0229dad0 @ 0x0229dad0, 0x48 bytes, Thumb
 * func_ov100_0229da7c @ 0x0229da7c, 0x54 bytes, Thumb
 * func_ov100_0229da40 @ 0x0229da40, 0x3c bytes, Thumb
 * func_ov100_0229da04 @ 0x0229da04, 0x3c bytes, Thumb
 * func_ov100_0229d9c0 @ 0x0229d9c0, 0x44 bytes, Thumb
 * func_ov100_0229d9a0 @ 0x0229d9a0, 0x20 bytes, Thumb
 * func_ov100_0229d968 @ 0x0229d968, 0x38 bytes, Thumb
 * func_ov100_0229d928 @ 0x0229d928, 0x40 bytes, Thumb
 * func_ov100_0229d90c @ 0x0229d90c, 0x1c bytes, Thumb
 * func_ov100_0229d8d0 @ 0x0229d8d0, 0x3c bytes, Thumb
 * func_ov100_0229d8b0 @ 0x0229d8b0, 0x20 bytes, Thumb
 * func_ov100_0229d824 @ 0x0229d824, 0x8c bytes, Thumb
 * func_ov100_0229d7d8 @ 0x0229d7d8, 0x4c bytes, Thumb
 * func_ov100_0229d788 @ 0x0229d788, 0x50 bytes, Thumb
 * func_ov100_0229d71c @ 0x0229d71c, 0x6c bytes, Thumb
 * func_ov100_0229d6d8 @ 0x0229d6d8, 0x44 bytes, Thumb
 * func_ov100_0229d69c @ 0x0229d69c, 0x3c bytes, Thumb
 */

typedef struct {
    char pad_00[0x2274];
    char sub;
    char pad_2275[0x6AC];
    unsigned char b1;
    char pad_2922;
    unsigned char b2;
} UnkStruct_0229db18;

struct UnkStruct_0229d7d8 {
    char pad_00[0x218c];
    char unk_218C;
    char pad_218D[0x790];
    unsigned char unk_291D;
    char pad_291E[2];
    unsigned char unk_2920;
};

typedef struct {
    char pad_00[0x218c];
    char unk_218C;
    char pad_218D[0x291d - 0x218c - 1];
    unsigned char unk_291D;
    char pad_291E[0x2920 - 0x291d - 1];
    unsigned char unk_2920;
    char pad_2921[0x2924 - 0x2920 - 1];
    unsigned char unk_2924;
} UnkStruct_0229d788;

typedef struct {
    int pad_00;
} UnkStruct_0229d71c;

typedef struct {
    char pad_00[0x225c];
    UnkStruct_0229d71c sub;
    char pad1[0x28d4 - 0x225c - sizeof(UnkStruct_0229d71c)];
    int unk_28D4;
    int unk_28D8;
    char pad_28DC[0x2920 - 0x28d8 - 4];
    unsigned char byte_field;
} UnkStruct_0229d71c_2;

struct UnkStruct_0229d69c {
    char pad_00[0x28d4];
    int unk_28D4;
    int unk_28D8;
};

extern int func_0208e484(void *);
extern void func_ov100_0229c3c0(void *);
extern void func_ov100_0229c4ec(void *);
extern void func_ov100_0229ca3c(void *);
extern void func_ov100_0229ca7c(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov002_02209f9c(void *ptr);
extern void func_ov100_0229ce24(void *);
extern int func_ov100_0229d4f4(UnkStruct_0229db18 *self, int index);
extern void func_ov100_0229cecc(UnkStruct_0229db18 *self);
extern void func_ov094_022999d8(void);
extern void func_ov100_0229cd10(int, unsigned char);
extern void func_ov100_0229c2b0(int, int);
extern int func_ov002_02209f70(int);
extern int func_ov100_0229c2c0(void *p, int x);
extern void func_ov100_0229c2a0(void *p, int x);
extern void func_ov094_022999c0(void);
extern int func_ov002_02209d8c(void *p);
extern void func_ov100_0229cd4c(void *p, unsigned char c);
extern void func_ov100_0229cdf4(void *p);
extern int func_0206fe54(void);
extern void func_ov100_0229cad0(void *);
extern int func_ov002_02208e28(void *);
extern int func_ov002_0220909c(char *p);
extern void func_ov002_022096d8(char *p, int v);
extern int func_0208e4bc(char *p);
extern void func_ov100_0229ca9c(char *p);
extern int func_ov002_02208e18(void *ptr);
extern void func_ov100_0229c970(void *ptr);
extern int func_ov002_0220b8ac(void *p, int arg);
extern void func_0208e5cc(void *p);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_ov002_02207d24(void *, int);
extern void func_ov100_0229cc3c(void *);
extern void func_ov100_0229d0c0(void *);
extern void func_ov100_0229ccb8(void *);
extern void func_ov100_0229d068(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
void func_ov002_02207cf8(unsigned char *);
int func_ov100_0229d194(unsigned char *, int);
void func_ov094_022999cc(void);
extern void func_ov100_0229cd7c(struct UnkStruct_0229d7d8 *self, int arg);
extern void func_ov100_0229ce58(struct UnkStruct_0229d7d8 *self);
extern void func_ov002_02209d68(void *sub, int a, int b);
extern int func_ov100_0229d42c(void *obj, int arg);
extern int func_ov100_0229d3d8(void *obj, int arg);
extern int func_ov002_02209d38(void *sub, int a, int b, int c);
extern int func_ov100_0229d620(int unused0, unsigned int unused1);
extern int func_ov100_0229d67c(void *receiver);
extern int func_ov100_0229d630(int unused0, unsigned int unused1);
extern int func_ov100_0229d648(int);

void func_ov100_0229d8b0(int r0);
void func_ov100_0229d788(UnkStruct_0229d788 *self, int v);
void func_ov100_0229d71c(void *obj, int arg1, int arg2);

void func_ov100_0229dbf8(void *p)
{
    if (func_0208e484((char *) p + 0x2274)) {
        unsigned char v = *(unsigned char *) ((char *) p + 0x2921);
        if (v == 0x1e) {
            func_ov100_0229c3c0(p);
        } else if (v == 0x1f) {
            func_ov100_0229c4ec(p);
        } else {
            func_ov100_0229ca3c(p);
        }
    }
}

void func_ov100_0229dbd0(void *r0)
{
    if (func_0208e484((char *) r0 + 0x2274)) {
        func_ov100_0229ca7c(r0);
        func_ov002_02208098((void *) (r0), 4);
    }
}

void func_ov100_0229dba0(void *arg)
{
    if (func_ov002_02209f9c((char *) arg + 0x2274) != 0) {
        func_ov100_0229d788((UnkStruct_0229d788 *) arg, (unsigned char) (*((unsigned char *) ((char *) arg + 0x2921))));
        func_ov002_02208098((void *) (arg), 0xc);
    }
}

void func_ov100_0229db70(void *obj)
{
    if (func_0208e484((char *) obj + 0x2274)) {
        func_ov002_02208098((void *) (obj), *(unsigned char *) ((char *) obj + 0x2924));
    }
    func_ov100_0229ce24(obj);
}

void func_ov100_0229db18(UnkStruct_0229db18 *self)
{
    if (func_ov002_02209f9c((void *) (&self->sub)) == 0) {
        if (self->b1 == self->b2) {
            func_ov100_0229d4f4(self, self->b2);
            func_ov100_0229cecc(self);
            func_ov002_02208098((void *) (self), 4);
            func_ov094_022999d8();
        } else {
            func_ov100_0229d71c((void *) self, (unsigned char) self->b2, 4);
        }
    } else {
        func_ov100_0229ce24((void *) self);
    }
}

void func_ov100_0229dad0(int arg0)
{
    if (func_ov002_02209f70(arg0 + 0x2274) == 0) {
        func_ov100_0229cd10(arg0, *(unsigned char *) (arg0 + 0x2923));
        func_ov100_0229c2b0(arg0, 0x40);
        func_ov002_02208098((void *) (arg0), 0xf);
        func_ov100_0229cecc((UnkStruct_0229db18 *) arg0);
    } else {
        func_ov002_02208098((void *) (arg0), 4);
    }
}

void func_ov100_0229da7c(unsigned char *param)
{
    if (func_0208e484(param + 0x2274) != 0) {
        func_ov002_02208098((void *) (param), param[0x2924]);
    }
    if (func_ov002_02209f9c(param + 0x2274) != 0) {
        if (func_ov100_0229c2c0(param, 0x40) != 0) {
            ((void) (func_ov100_0229c2a0(param, 0x40)), func_ov094_022999c0());
        }
        func_ov100_0229ce24(param);
    }
}

void func_ov100_0229da40(void *self)
{
    if (func_ov002_02209d8c((char *) self + 0x225c)) {
        func_ov100_0229cd4c(self, *(unsigned char *) ((char *) self + 0x2920));
        func_ov100_0229d8b0((int) self);
        func_ov094_022999d8();
    } else {
        func_ov100_0229cdf4(self);
    }
}

void func_ov100_0229da04(void *param)
{
    if (func_ov002_02208e28((char *) param + 0x22d8) != 0) {
        if (func_0206fe54() != 0) {
            func_ov100_0229cad0(param);
            func_ov002_02208098((void *) (param), 6);
        } else {
            func_ov002_02208098((void *) (param), 2);
        }
    }
}

int func_ov100_0229d9c0(char *self)
{
    int result;
    result = func_ov002_0220909c(self + 0x22d8);
    if (result == 0) {
        return result;
    }
    func_ov002_022096d8(self + 0x22d8, 0);
    if (func_0208e4bc(self + 0x2274)) {
        func_ov100_0229ca9c(self);
    }
    return (int) func_ov002_02208098((void *) (self), 0x13);
}

void func_ov100_0229d9a0(void *ptr)
{
    if (func_ov002_02208e18((char *) ptr + 0x22d8)) {
        func_ov100_0229c970(ptr);
    }
}

void func_ov100_0229d968(void *self)
{
    if (func_ov002_0220b8ac((char *) self + 0x26cc, 0) != 0) {
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0x2924));
        func_0208e5cc((char *) self + 0x2274);
    }
}

void func_ov100_0229d928(unsigned char *p)
{
    if (p[0x2928] != 0) {
        p[0x2928] = p[0x2928] - 1;
        return;
    }
    p[0x8c] = 4;
    func_ov002_022080a0((void *) (p), 1);
    func_ov002_02207d24(p + 0x218c, 0);
    func_ov100_0229cc3c(p);
}

void func_ov100_0229d90c(void *arg0)
{
    func_ov100_0229cc3c(arg0);
    func_ov100_0229d0c0(arg0);
    func_ov002_02208098((void *) (arg0), 0);
}

void func_ov100_0229d8d0(void *self)
{
    ((unsigned char *) self)[0x291f] = 0x20;
    func_ov100_0229ccb8(self);
    func_ov002_02207fc0(self);
    func_ov100_0229cecc((UnkStruct_0229db18 *) self);
    func_ov002_02208098((void *) (self), 4);
    func_ov100_0229d068(self, ((unsigned char *) self)[0x2921]);
}

void func_ov100_0229d8b0(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov100_0229d90c((void *) r4);
    } else {
        func_ov100_0229d8d0((void *) r4);
    }
}

void func_ov100_0229d824(unsigned char *base, int param)
{
    unsigned char g1, g2;
    int val1, val2;

    base[0x291e] = (unsigned char) param;
    func_ov002_02208098((void *) (base), 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    val1 = func_ov100_0229d42c((void *) base, base[0x291e]) - g1;
    *(int *) (base + 0x28cc) = val1;
    val2 = func_ov100_0229d3d8((void *) base, base[0x291e]) - g2;
    *(int *) (base + 0x28d0) = val2;
    base[0x291f] = (unsigned char) param;
    func_ov002_02207cf8(base + 0x218c);
    if (func_ov100_0229d194(base, param) != 0) {
        func_ov100_0229c2a0((void *) base, 4);
    } else {
        func_ov100_0229c2b0((int) base, 4);
        func_ov094_022999cc();
    }
}

void func_ov100_0229d7d8(struct UnkStruct_0229d7d8 *self, int arg)
{
    self->unk_2920 = arg;
    func_ov002_02207d24(&self->unk_218C, 1);
    func_ov100_0229cd7c(self, arg);
    if (self->unk_291D == 1) {
        func_ov002_02208098((void *) (self), 3);
    }
    ((void) (func_ov100_0229ce58(self)), func_ov094_022999c0());
}

void func_ov100_0229d788(UnkStruct_0229d788 *self, int v)
{
    self->unk_2920 = v;
    func_ov002_02207d24(&self->unk_218C, 1);
    func_ov100_0229cd7c((struct UnkStruct_0229d7d8 *) self, v);
    if (self->unk_291D == 1) {
        self->unk_2924 = 5;
    }
    func_ov100_0229ce24((void *) self);
    func_ov094_022999c0();
}

void func_ov100_0229d71c(void *obj, int arg1, int arg2)
{
    UnkStruct_0229d71c_2 *o = (UnkStruct_0229d71c_2 *) obj;

    o->byte_field = arg1;
    func_ov002_02209d68(&o->sub, o->unk_28D4, o->unk_28D8);
    {
        int r7 = func_ov100_0229d42c(obj, arg1);
        int r2 = func_ov100_0229d3d8(obj, arg1);
        func_ov002_02209d38(&o->sub, r7, r2, arg2);
    }
    func_ov002_02209d8c(&o->sub);
    func_ov100_0229cdf4(obj);
    func_ov002_02208098((void *) (obj), 0x10);
}

void func_ov100_0229d6d8(int a, int b, int c)
{
    int value_r4 = 0x20;
    int value_r6 = b;
    int value_r5 = a;

    if (c >= 0x6c) {
        if (func_ov100_0229d620(a, b)) {
            value_r4 = func_ov100_0229d67c((void *) value_r5);
        }
    } else {
        if (func_ov100_0229d630(a, b)) {
            value_r4 = func_ov100_0229d648(value_r5);
        }
    }

    if (value_r4 != 0x20) {
        value_r6 = value_r4;
    }

    func_ov100_0229d71c((void *) value_r5, value_r6, 4);
}

void func_ov100_0229d69c(struct UnkStruct_0229d69c *a0, int a1, int a2)
{
    func_ov100_0229cd7c((struct UnkStruct_0229d7d8 *) a0, a1);
    a0->unk_28D4 = func_ov100_0229d42c(a0, a1);
    a0->unk_28D8 = func_ov100_0229d3d8(a0, a1);
    func_ov100_0229d71c(a0, a2, 4);
}
