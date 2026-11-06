/* design_picker_2: 21 functions, module ov125
 * mwccarm 1.2/base -O4,s
 * func_ov125_022a0000 @ 0x022a0000, 0x30 bytes, Thumb
 * func_ov125_0229ffc4 @ 0x0229ffc4, 0x3c bytes, Thumb
 * func_ov125_0229ff80 @ 0x0229ff80, 0x44 bytes, Thumb
 * func_ov125_0229ff60 @ 0x0229ff60, 0x20 bytes, Thumb
 * func_ov125_0229fefc @ 0x0229fefc, 0x64 bytes, Thumb
 * func_ov125_0229fee4 @ 0x0229fee4, 0x16 bytes, Thumb
 * func_ov125_0229feb8 @ 0x0229feb8, 0x2c bytes, Thumb
 * func_ov125_0229fe98 @ 0x0229fe98, 0x20 bytes, Thumb
 * func_ov125_0229fe58 @ 0x0229fe58, 0x40 bytes, Thumb
 * func_ov125_0229fe4c @ 0x0229fe4c, 0xc bytes, Thumb
 * func_ov125_0229fe40 @ 0x0229fe40, 0xc bytes, Thumb
 * func_ov125_0229fdc4 @ 0x0229fdc4, 0x7c bytes, Thumb
 * func_ov125_0229fd3c @ 0x0229fd3c, 0x88 bytes, Thumb
 * func_ov125_0229fd04 @ 0x0229fd04, 0x38 bytes, Thumb
 * func_ov125_0229fc90 @ 0x0229fc90, 0x74 bytes, Thumb
 * func_ov125_0229fc84 @ 0x0229fc84, 0xc bytes, Thumb
 * func_ov125_0229fc24 @ 0x0229fc24, 0x60 bytes, Thumb
 * func_ov125_0229fbd0 @ 0x0229fbd0, 0x54 bytes, Thumb
 * func_ov125_0229fb7c @ 0x0229fb7c, 0x54 bytes, Thumb
 * func_ov125_0229fb34 @ 0x0229fb34, 0x48 bytes, Thumb
 * func_ov125_0229fb1c @ 0x0229fb1c, 0x18 bytes, Thumb
 */

struct UnkStruct_0229fc24 {
    char pad_00[0x87b];
    unsigned char unk_87B;
};

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x7ee];
    unsigned char unk_87B;
    unsigned char unk_87C;
    unsigned char unk_87D;
} UnkStruct_0229fbd0;

struct UnkStruct_0229fb1c {
    unsigned char pad_00[0x87c];
    unsigned char unk_87C;
};

extern int func_0208e484(void *ptr);
extern void *func_ov002_0220a720(void *ptr, int arg);
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);
extern int func_0206fe54(void);
extern void func_ov125_0229f948(int);
extern int func_ov002_02208e28(int);
extern int func_ov002_0220909c(void *ptr);
extern void func_ov002_022096d8(void *ptr, int value);
extern int func_0208e4bc(void *ptr);
extern void func_ov125_0229f994(void *ptr);
extern int func_ov002_02208e18(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov125_0229faf8(void *arg0);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void func_ov125_0229f75c(unsigned short *object, unsigned short mask);
extern void func_0206fc4c(int);
extern int func_ov002_02207d24(void *, int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern void func_0200467c(int);
extern unsigned char data_ov125_022a0a04[];
extern unsigned char data_ov125_022a0a10[];
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern int func_ov002_0220a784(int a, int b);
extern void func_0208aa60(void *dst, int a, int b);
extern int func_02062e50(void *p);
extern int func_020984e8(void);
extern int func_020996b8(int x);
extern int func_02072bb0(int x, unsigned char c);
extern int func_02072d4c(int x);
extern void func_02072ea4(int x, void *p);
extern void *func_0208aecc(void *p);
extern int func_02051984(void *dst, void *src);
extern void func_0208aa48(void *dst, void *src);
extern void func_0208aeb8(void *p);
extern void *func_02062e00(void *p);
extern void func_ov002_02207cf8(void *);
extern void func_ov002_02208d30(char *p, int a);
extern unsigned char func_0206fca4(void);
extern int func_ov002_02208d4c(char *p, int a, int b);
extern void func_ov002_02208c58(void *a, void *b, int c);
extern void func_ov002_022098ec(void *addr, int a, int b);
extern void func_ov002_0220970c(void *addr, int n);
extern void func_0206fc80(int);
extern void func_ov125_0229f928(char *);
extern void func_ov002_0220a374(char *, int);
extern int func_ov125_0229f76c(void *p, int x);

void func_ov125_0229fe58(void *arg0);
void func_ov125_0229fd04(void *r0);
void func_ov125_0229fbd0(UnkStruct_0229fbd0 *p);
void func_ov125_0229fb7c(char *obj);
int func_ov125_0229fb34(void *p);
int func_ov125_0229fb1c(struct UnkStruct_0229fb1c *self);

void func_ov125_022a0000(void *self)
{
    if (func_0208e484((char *) self + 0x644)) {
        func_ov002_0220a720((char *) self + 0x6a8, 9);
        func_ov002_02208098(self, 10);
    }
}

void func_ov125_0229ffc4(int param)
{
    int r4 = param;
    if (func_ov002_02208e28(r4 + 0x180) != 0) {
        if (func_0206fe54() != 0) {
            func_ov125_0229f948(r4);
            func_ov002_02208098((void *) r4, 3);
        } else {
            func_ov002_02208098((void *) r4, 1);
        }
    }
}

void func_ov125_0229ff80(void *param)
{
    if (func_ov002_0220909c((char *) param + 0x180)) {
        func_ov002_022096d8((char *) param + 0x180, 0);
        if (func_0208e4bc((char *) param + 0x644)) {
            func_ov125_0229f994(param);
        }
        func_ov002_02208098(param, 9);
    }
}

void func_ov125_0229ff60(void *p)
{
    if (func_ov002_02208e18((char *) p + 0x180)) {
        func_ov125_0229fbd0((UnkStruct_0229fbd0 *) p);
    }
}

void func_ov125_0229fefc(void *arg0)
{
    if (func_ov002_0220a700((char *) arg0 + 0x6a8)) {
        if (func_0208e4bc((char *) arg0 + 0x644)) {
            int r4 = func_ov002_0220a6e0((char *) arg0 + 0x6a8);
            int r6 = func_ov002_0220a768((char *) arg0 + 0x6a8, -1);
            int r2 = func_ov002_0220a72c((char *) arg0 + 0x6a8, -1);
            func_ov002_0220a0b4((char *) arg0 + 0x644, r4 + r6, r4 + r2);
        }
    } else {
        func_ov125_0229fe58(arg0);
    }
}

void func_ov125_0229fee4(void *p)
{
    void *r4 = p;
    func_ov125_0229faf8((void *) p);
    func_ov002_02208098(r4, 0);
}

void func_ov125_0229feb8(void *self)
{
    ((unsigned char *) self)[0x87a] = 9;
    func_ov125_0229fb7c((char *) self);
    func_ov002_02207fc0(self);
    func_ov125_0229fd04(self);
    func_ov002_02208098(self, 2);
}

void func_ov125_0229fe98(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov125_0229fee4((void *) r4);
    } else {
        func_ov125_0229feb8((void *) r4);
    }
}

void func_ov125_0229fe58(void *arg0)
{
    void *r4 = arg0;
    func_ov125_0229faf8(r4);
    func_ov002_02207d24((char *) r4 + 0x574, 1);
    func_ov125_0229f75c(r4, 0x10);
    *(unsigned char *) ((char *) r4 + 0x8c) = 3;
    func_0206fc4c(0);
    func_ov002_022080a0(r4, 1);
    func_0200467c(0x28);
}

unsigned char func_ov125_0229fe4c(int unused, int index)
{
    return data_ov125_022a0a04[index];
}

int func_ov125_0229fe40(int unused, int index)
{
    return data_ov125_022a0a10[index] - 16;
}

int func_ov125_0229fdc4(int param0)
{
    unsigned char i;
    int c1, c2, lo1, hi1, lo2, hi2;
    if (func_ov002_0220a784(param0 + 0x6a8, 9) != 0) {
        return 8;
    }
    c1 = data_021f6c58;
    c2 = data_021f6c54;
    lo1 = c1 - 0x10;
    hi1 = c1 + 0x10;
    lo2 = c2 - 0x10;
    hi2 = c2 + 0x10;
    for (i = 0; i < 8; i++) {
        int v = (int) func_ov125_0229fe4c(param0, i);
        if (lo1 >= v) {
            continue;
        }
        if (v >= hi1) {
            continue;
        }
        v = func_ov125_0229fe40(param0, i);
        if (lo2 >= v) {
            continue;
        }
        if (v >= hi2) {
            continue;
        }
        return i;
    }
    return 9;
}

void func_ov125_0229fd3c(void *self)
{
    unsigned char a[0x24];
    unsigned char b[0x30];
    int v, r4;

    v = func_ov125_0229fe40((int) self, (unsigned char) (*((unsigned char *) self + 0x87a)));
    r4 = v - 0x84;
    if (func_0206fe54()) {
        r4 -= 0xa;
    }

    func_0208aa60((char *) self + 0x574,
                  (int) func_ov125_0229fe4c((int) self, (unsigned char) (*((unsigned char *) self + 0x87a))) - 0x78, r4);

    func_02072ea4(func_02072d4c(func_02072bb0(func_020996b8(((void) (func_02062e50(a)), func_020984e8())),
                                              *((unsigned char *) self + 0x87a))),
                  a);

    func_0208aecc(b);
    func_02051984(b, a);
    func_0208aa48((char *) self + 0x574, b);
    func_0208aeb8(b);
    func_02062e00(a);
}

void func_ov125_0229fd04(void *r0)
{
    unsigned char r2;
    void *r1;

    r2 = *(unsigned char *) ((char *) r0 + 0x87c);
    if (r2 <= 7) {
        *(unsigned char *) ((char *) r0 + 0x87a) = r2;
        func_ov002_02207cf8((char *) r0 + 0x574);
    } else {
        func_ov002_02207d24((char *) r0 + 0x574, 1);
    }
}

void func_ov125_0229fc90(char *self)
{
    unsigned int v;
    func_ov002_02208d30(self + 0x568, 1);
    v = func_0206fca4() - 4;
    switch (v) {
        case 1:
        case 4:
        case 5:
            func_ov002_02208d4c(self + 0x568, 0x91, 0);
            break;
        case 0:
        case 3:
        case 6:
            func_ov002_02208d4c(self + 0x568, 0x72, 0);
            break;
        case 2:
        default:
            func_ov002_02208d4c(self + 0x568, 0x28, 0);
            break;
    }
    func_ov002_02208d4c(self + 0x568, 2, 1);
}

unsigned char func_ov125_0229fc84(unsigned char *ptr, int offset)
{
    return *(ptr + offset + 0x56d);
}

void func_ov125_0229fc24(struct UnkStruct_0229fc24 *self)
{
    int v1, v2;

    func_ov002_02208c58((char *) self + 0x180, (char *) self + 0x568, 0);
    v1 = (int) func_ov125_0229fe4c((int) self, self->unk_87B) - 0x18;
    v2 = func_ov125_0229fe40((int) self, self->unk_87B) - 0x10;
    func_ov002_022098ec((char *) self + 0x180, v1, v2);
    func_ov002_0220970c((char *) self + 0x180, 0);
    func_ov002_02208098((void *) self, 7);
}

void func_ov125_0229fbd0(UnkStruct_0229fbd0 *p)
{
    switch (p->unk_87D) {
        case 0:
            func_0206fc80(p->unk_87B);
            func_0206fc4c(1);
            p->unk_8C = 3;
            func_ov002_02207d24((char *) p + 0x574, 1);
            func_ov002_022080a0(p, 1);
            break;
        case 1:
        default:
            func_ov125_0229fe98((int) p);
            break;
    }
}

void func_ov125_0229fb7c(char *obj)
{
    int a, b;

    a = func_ov125_0229fb34((void *) obj);
    b = func_ov125_0229fb1c((struct UnkStruct_0229fb1c *) obj);
    func_ov002_0220a0b4((void *) (obj + 0x644), a, b);
    if (*(unsigned char *) (obj + 0x87c) == 8) {
        func_ov002_0220a374(obj + 0x644, 7);
    } else {
        func_ov002_0220a374(obj + 0x644, 1);
    }
    func_ov125_0229f928(obj);
}

int func_ov125_0229fb34(void *p)
{
    int a = (int) func_ov125_0229fe4c((int) p, ((unsigned char *) p)[0x87c]);
    if (func_ov125_0229f76c(p, 8) != 0) {
        a += 0x100;
    } else if (func_ov125_0229f76c(p, 4) != 0) {
        a -= 0x100;
    }
    return a + 11;
}

int func_ov125_0229fb1c(struct UnkStruct_0229fb1c *self)
{
    return func_ov125_0229fe40((int) self, (unsigned char) self->unk_87C) - 11;
}
