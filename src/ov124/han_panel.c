/* han_panel: 14 functions, module ov124
 * mwccarm 1.2/base -O4,s
 * func_ov124_0229f460 @ 0x0229f460, 0x30 bytes, Thumb
 * func_ov124_0229f43c @ 0x0229f43c, 0x24 bytes, Thumb
 * func_ov124_0229f398 @ 0x0229f398, 0xa4 bytes, Thumb
 * func_ov124_0229f378 @ 0x0229f378, 0x1e bytes, Thumb
 * func_ov124_0229f320 @ 0x0229f320, 0x58 bytes, Thumb
 * func_ov124_0229f2e4 @ 0x0229f2e4, 0x3c bytes, Thumb
 * func_ov124_0229f2dc @ 0x0229f2dc, 0x8 bytes, Thumb
 * func_ov124_0229f2c8 @ 0x0229f2c8, 0x14 bytes, Thumb
 * func_ov124_0229f27c @ 0x0229f27c, 0x4a bytes, Thumb
 * func_ov124_0229f0ec @ 0x0229f0ec, 0x190 bytes, Thumb
 * func_ov124_0229ef4c @ 0x0229ef4c, 0x1a0 bytes, Thumb
 * func_ov124_0229ef08 @ 0x0229ef08, 0x44 bytes, Thumb
 * func_ov124_0229eeb8 @ 0x0229eeb8, 0x50 bytes, Thumb
 * func_ov124_0229eea0 @ 0x0229eea0, 0x16 bytes, Thumb
 */

extern void *data_021fbe94;
extern int func_0206fca4(void);
extern int **func_02070be8(void *unused0);
extern int func_ov124_0229f27c(int a);

typedef struct {
    unsigned char pad_00[0xe8];
    unsigned char unk_E8;
} UnkStruct_0229f0ec;

extern int func_02002ca4(void *a, void *b, void *c);
extern int func_02002cd8(const void *a, void *b, int c, int d, int e);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02088df8(int p0, void *p1, void *p2, void *p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10,
                          int p11);
extern int func_ov124_0229f0ec(UnkStruct_0229f0ec *o, void *p1, int p2);

extern void __cxa_vec_ctor(void *self, int a, int b, void *fp1, void *fp2);
extern void *func_ov002_0220b3c4(void *ptr);

extern void *func_02070c08(void *unused0);

#define VisitElement_02070c08 (void *) func_02070c08
#define VisitElement_02070be8 (void *) func_02070be8

void *func_ov124_0229f460(void *self)
{
    __cxa_vec_ctor(self, 1, 0x6c, VisitElement_02070c08, VisitElement_02070be8);
    func_ov002_0220b3c4((char *) self + 0x6c);
    return self;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8

extern void *func_ov002_0220b3a4(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));

#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov124_0229f43c(void *p)
{
    func_ov002_0220b3a4((char *) p + 0x6c);
    __cxa_vec_cleanup(p, 1, 0x6c, VisitElement_02070be8);
    return p;
}

#undef VisitElement_02070be8

extern int func_0207094c(void *r0, int r1);
extern void func_02070a04(void *r0, int r1, int r2);

extern char data_ov124_0229f674;

void func_ov124_0229f398(void *r0, void *r1, int r2)
{
    func_ov124_0229f0ec(r0, r1, 5);
    func_02002ca4(&data_ov124_0229f674, data_021fbe94, (void *) r2);

    switch (func_0206fca4() - 4) {
        case 0:
        case 3:
        case 6:
            func_0207094c(r0, 0x3a);
            break;
        case 1:
            func_0207094c(r0, 0x90);
            break;
        case 4:
        case 5:
            func_0207094c(r0, 0x92);
            break;
        case 2:
            func_0207094c(r0, 0x49);
            break;
        default:
            func_0207094c(r0, 0x3a);
            break;
    }

    func_02070adc((int) r0, (int) r1, 0x11, 0xd, 4, 1, 0);
    func_02070a04(r0, 1, 0);
}

int func_ov124_0229f378(int a, int b)
{
    int c;
    c = func_ov124_0229f27c(a);
    return func_ov124_0229f0ec((UnkStruct_0229f0ec *) a, (void *) b, c);
}

void func_ov124_0229f320(int a0)
{
    int s;
    unsigned int v;

    v = func_ov124_0229f27c(a0);

    switch (v) {
        case 0:
            s = 0xd;
            break;
        case 1:
            s = 8;
            break;
        case 2:
            s = 0x14;
            break;
        case 3:
            s = 5;
            break;
        case 4:
            s = 0xa;
            break;
    }

    func_02070adc(a0, 3, 0x11, s, 4, 1, 0);
}

extern void func_02070978(int a, int b);

void func_ov124_0229f2e4(int a)
{
    int val;
    switch (func_ov124_0229f27c(a)) {
        case 0:
        case 1:
            val = 2;
            break;
        case 2:
        case 3:
        case 4:
            val = 0;
            break;
    }
    func_02070978(a, val);
}

extern void func_020708e4(void *argument0, void *argument1, void *argument2);

void func_ov124_0229f2dc(void *argument0, void *argument1, void *argument2)
{
    func_020708e4(argument0, argument1, argument2);
}

extern void func_02070854(int, int, int, int, int);

void func_ov124_0229f2c8(int a1, int a2, int a3, int a4, int a5)
{
    func_02070854(a1, a2, a3, a4, a5);
}

int func_ov124_0229f27c(int a)
{
    switch (func_0206fca4() - 15) {
        case 0:
        case 1:
        case 2:
        case 9:
        case 10:
        case 11:
        case 12:
            return 1;
        case 6:
            return 3;
        case 3:
            return 1;
        case 4:
        case 5:
        case 7:
        case 8:
        default:
            return 0;
    }
}

extern const unsigned char data_ov124_0229f628[];
extern const unsigned char data_ov124_0229f638[];
extern const unsigned char data_ov124_0229f648[];
extern const unsigned char data_ov124_0229f65c[];
extern void *data_ov124_0229f578[];

extern int func_02002c6c(const void *a, void *b, void *c, int d, int e, int f);
extern int func_02002d14(const void *a, void *b, void *c, int d, int e, int f);
extern int func_02064328(void *dst, const void *src, int n);

int func_ov124_0229f0ec(UnkStruct_0229f0ec *o, void *p1, int p2)
{
    void *heap;
    char buf[0x24];

    heap = data_021fbe94;
    func_02002c6c(data_ov124_0229f628, heap, p1, 0x10, 0x10, 0x169);
    func_02002d14(data_ov124_0229f638, heap, p1, 1, 1, 6);
    switch (func_0206fca4()) {
        case 4:
        case 5:
        case 7:
        case 8:
            o->unk_E8 = 0;
            break;
        case 6:
        case 9:
            o->unk_E8 = 2;
            break;
        case 0xb:
            o->unk_E8 = 1;
            break;
        case 0xc:
            o->unk_E8 = 3;
            break;
        case 0xd:
            o->unk_E8 = 4;
            break;
        case 0xe:
            o->unk_E8 = 7;
            break;
        case 0xf:
        case 0x1a:
        case 0x1b:
            o->unk_E8 = 5;
            break;
        case 0x10:
        case 0x18:
        case 0x19:
            o->unk_E8 = 6;
            break;
        case 0x11:
            o->unk_E8 = 8;
            break;
        case 0x12:
            o->unk_E8 = 0xe;
            break;
        case 0x13:
            o->unk_E8 = 0xd;
            break;
        case 0x14:
            o->unk_E8 = 0xc;
            break;
        case 0x15:
            o->unk_E8 = 0xb;
            break;
        case 0x16:
            o->unk_E8 = 9;
            break;
        case 0x17:
            o->unk_E8 = 0xa;
            break;
        case 0xa:
            o->unk_E8 = 0xf;
            break;
        default:
            o->unk_E8 = 0;
            break;
    }
    func_02064328(buf, data_ov124_0229f648, o->unk_E8);
    func_02002c6c(buf, heap, p1, 0x113, 0x113, 0x126);
    func_02002cd8(data_ov124_0229f65c, heap, (int) p1, o->unk_E8, 0xe);
    return func_02002ca4(data_ov124_0229f578[p2], heap, p1);
}

typedef struct {
    unsigned char pad_00[0x6c];
    unsigned char unk_6C;
    unsigned char pad_6D[0x7b];
    unsigned char unk_E8;
    unsigned char unk_E9;
} UnkStruct_0229ef4c;

extern void *data_ov124_0229f4a0[];
extern const unsigned char data_ov124_0229f5d0[];
extern const unsigned char data_ov124_0229f610[];

extern void *func_02064b2c(void *a, void *b, int c, void *d);
extern int func_02002a88(void *a, int b, int c, int d, int e);
extern void func_ov002_0220b36c(void *self, const void *data, int a, int b);
extern void func_ov002_0220b318(void *self, int a);
extern void func_020e993c(void *a, void *b);

void func_ov124_0229ef4c(UnkStruct_0229ef4c *o, int p1)
{
    void *heap;
    void *base;
    unsigned char *q;
    int i;
    int t;
    int local;
    int v;

    t = o->unk_E8;
    heap = data_021fbe94;
    base = func_02064b2c(data_ov124_0229f4a0[t / 5], heap, ~3, &local);
    q = (unsigned char *) base + (t % 5) * 0xc0;
    v = 0x15a;
    for (i = 0; i < 6; i++) {
        func_02002a88(q, 8, v, v, v + 5);
        q += 0x400;
        v += 0x20;
    }
    func_020e993c(heap, base);
    func_02002cd8(data_ov124_0229f610, heap, 8, o->unk_E8, p1);
    o->unk_E9 = p1;
    func_ov002_0220b36c(&o->unk_6C, data_ov124_0229f5d0, 0xe, 2);
    switch (func_0206fca4()) {
        case 0xb:
            func_ov002_0220b318(&o->unk_6C, 0x3b);
            break;
        case 0xf:
            func_ov002_0220b318(&o->unk_6C, 0xe6);
            break;
        case 0x10:
            func_ov002_0220b318(&o->unk_6C, 0xe7);
            break;
        case 0x18:
        case 0x19:
            func_ov002_0220b318(&o->unk_6C, 0xe9);
            break;
        case 0x1a:
        case 0x1b:
            func_ov002_0220b318(&o->unk_6C, 0xe8);
            break;
        case 0xc:
            func_ov002_0220b318(&o->unk_6C, 0x42);
            break;
        case 0xd:
            func_ov002_0220b318(&o->unk_6C, 0x44);
            break;
        case 0xe:
            func_ov002_0220b318(&o->unk_6C, 0x48);
            break;
        case 0x12:
            func_ov002_0220b318(&o->unk_6C, 0x4e);
            break;
        case 0x13:
            func_ov002_0220b318(&o->unk_6C, 0x4d);
            break;
        case 0x14:
            func_ov002_0220b318(&o->unk_6C, 0x4f);
            break;
        case 0x15:
            func_ov002_0220b318(&o->unk_6C, 0x45);
            break;
        case 0x16:
            func_ov002_0220b318(&o->unk_6C, 0x46);
            break;
        case 0x11:
            func_ov002_0220b318(&o->unk_6C, 0x4c);
            break;
        case 0x17:
            func_ov002_0220b318(&o->unk_6C, 0x41);
            break;
    }
}

extern int data_ov124_0229f590;

void func_ov124_0229ef08(unsigned char *a, void *b, void *c)
{
    func_02088df8(1, &data_ov124_0229f590, (char *) b + 0x80, (char *) c + 0x60, a[0xe9], 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

extern void func_ov002_0220b1a4(void *p0, void *p1, void *p2, int p3);
extern int data_ov124_0229f5b0;

void func_ov124_0229eeb8(void *arg0, void *arg1, void *arg2)
{
    func_ov002_0220b1a4((char *) arg0 + 0x6c, arg1, arg2, -1);
    func_02088df8(1, &data_ov124_0229f5b0, (char *) arg1 + 0x80, (char *) arg2 + 0x60,
                  *(unsigned char *) ((char *) arg0 + 0xe9), 2, 0x1000, 0x1000, 0, -1, 0, 0);
}

extern void func_02070b84(void *);
extern void func_ov002_0220b290(void *);

void func_ov124_0229eea0(char *p)
{
    func_02070b84(p);
    p += 0x6c;
    func_ov002_0220b290(p);
}
