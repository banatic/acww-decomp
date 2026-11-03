/* post_clerk_3: 12 functions, module ov054
 * mwccarm 1.2/base -O4,s
 * func_ov054_022622a8 @ 0x022622a8, 0x68 bytes, Thumb
 * func_ov054_0226228c @ 0x0226228c, 0x1c bytes, Thumb
 * func_ov054_02262260 @ 0x02262260, 0x2c bytes, Thumb
 * func_ov054_0226225c @ 0x0226225c, 0x4 bytes, Thumb
 * func_ov054_02262258 @ 0x02262258, 0x4 bytes, Thumb
 * func_ov054_02262208 @ 0x02262208, 0x50 bytes, Thumb
 * func_ov054_022621bc @ 0x022621bc, 0x4c bytes, Thumb
 * func_ov054_02262188 @ 0x02262188, 0x34 bytes, Thumb
 * func_ov054_02262134 @ 0x02262134, 0x54 bytes, Thumb
 * func_ov054_02262130 @ 0x02262130, 0x4 bytes, Thumb
 * func_ov054_022620cc @ 0x022620cc, 0x64 bytes, Thumb
 * func_ov054_022620c8 @ 0x022620c8, 0x4 bytes, Thumb
 */

struct UnkStruct_022622a8 {
    char pad_00[0x350];
    char sub1[0x214];
    char sub2[0x2a8];
    int unk_80C;
};

struct S020682e0 {
    int pad_00;
    int unk_04;
};

extern unsigned char data_ov054_0226297c[];
extern int func_ov054_02260474(void *self);
int func_ov054_02262494(struct UnkStruct_022622a8 *self);
void func_0201af1c(void *ptr, unsigned char val);
int func_02019e00(void *ptr);
int func_02019de8(void *ptr);
extern int func_020147e0(int a, int b, int c);
extern int func_02014868(void *);
extern int func_0203e020(void *);
extern void func_ov054_02262528(void *, int);
extern int func_02019d0c(void *ptr, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern unsigned short data_020c80f8;
extern int *func_02095794(int param);
extern struct S020682e0 *func_020682e0(int);
extern void func_020b22f4(void);
extern int func_0204e414(void);
extern int func_0204e188(int, void *, void *, void *);
extern int func_020b5e10(void);
extern int func_020b63f4(int, int, void *, int, int, int, int);

int func_ov054_022622a8(struct UnkStruct_022622a8 *self)
{
    func_ov054_02260474(self);
    if (func_ov054_02262494(self) != 0) {
        func_ov054_02262528((void *) self, 3);
        func_0201af1c(&self->sub1, data_ov054_0226297c[self->unk_80C]);
        return 1;
    } else {
        if (func_02019e00(&self->sub2) == 6) {
            if (func_02019de8(&self->sub2) != 0) {
                func_ov054_02262528((void *) self, 6);
            }
        }
        return 1;
    }
}

int func_ov054_0226228c(int a)
{
    func_020147e0(a + 0x618, 1, 0);
    return 1;
}

int func_ov054_02262260(void *self)
{
    if (func_02014868((char *) self + 0x618) == 0) {
        func_0203e020(self);
        func_ov054_02262528(self, 5);
    }
    return 1;
}

int func_ov054_0226225c(void)
{
    return 1;
}

int func_ov054_02262258(void)
{
    return 1;
}

int func_ov054_02262208(char *r4)
{
    struct Args {
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
        int g;
    } args;

    func_0201af1c(r4 + 0x350, 0);

    args.a = 0;
    args.b = 0;
    args.c = *(short *) (r4 + 0x804);
    args.d = 0;
    args.e = 0;
    args.f = data_020c80f8;
    args.g = 0;

    func_02019d0c(r4 + 0x564, 3, 1, 0, args.a, args.b, args.c, args.d, args.e, args.f, args.g);

    return 1;
}

int func_ov054_022621bc(void *p)
{
    func_ov054_02260474(p);
    if (func_ov054_02262494((struct UnkStruct_022622a8 *) p) != 0) {
        func_ov054_02262528(p, 3);
        return 1;
    }
    if (func_02019e00((char *) p + 0x564) == 3) {
        if (func_02019de8((char *) p + 0x564) != 0) {
            func_ov054_02262528(p, 2);
        }
    }
    return 1;
}

int func_ov054_02262188(int param)
{
    func_02019d0c((void *) (param + 0x564), 10, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov054_02262134(char *p)
{
    volatile int local[4];
    int *data;

    func_ov054_02260474(p);
    data = func_02095794(4);
    local[0] = data[0];
    local[1] = data[1];
    local[2] = data[2];

    if (func_02019e00((void *) (p + 0x564)) == 10) {
        if (func_02019de8((void *) (p + 0x564)) != 0) {
            *(short *) ((char *) p + 0x812) = 24;
            func_ov054_02262528((void *) p, 2);
        }
    }
    return 1;
}

int func_ov054_02262130(void)
{
    return 1;
}

int func_ov054_022620cc(void *obj)
{
    int local2;
    int local3;
    int t;
    struct {
        int a;
        int b;
        int c;
    } local1;

    if (func_020682e0(0)->unk_04 == 5) {
        func_020b22f4();
        t = func_0204e414();
        if (t != 0) {
            if (func_0204e188(t, &local1.a, &local2, &local3) != 0) {
                local1.c += 0x1000;
                func_020b63f4(func_020b5e10(), 0, &local1.a, 0x0ec00000, 0, 2, 2);
            }
        }
        func_ov054_02262528(obj, 5);
    }
    return 1;
}

int func_ov054_022620c8(void)
{
    return 1;
}
