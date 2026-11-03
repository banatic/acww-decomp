/* pockets_pick: 17 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229c660 @ 0x0229c660, 0x20 bytes, Thumb
 * func_ov101_0229c624 @ 0x0229c624, 0x3c bytes, Thumb
 * func_ov101_0229c5dc @ 0x0229c5dc, 0x48 bytes, Thumb
 * func_ov101_0229c5b8 @ 0x0229c5b8, 0x22 bytes, Thumb
 * func_ov101_0229c548 @ 0x0229c548, 0x70 bytes, Thumb
 * func_ov101_0229c51c @ 0x0229c51c, 0x2c bytes, Thumb
 * func_ov101_0229c4e0 @ 0x0229c4e0, 0x3c bytes, Thumb
 * func_ov101_0229c4ac @ 0x0229c4ac, 0x34 bytes, Thumb
 * func_ov101_0229c480 @ 0x0229c480, 0x2c bytes, Thumb
 * func_ov101_0229c42c @ 0x0229c42c, 0x54 bytes, Thumb
 * func_ov101_0229c330 @ 0x0229c330, 0xfc bytes, Thumb
 * func_ov101_0229c2c0 @ 0x0229c2c0, 0x70 bytes, Thumb
 * func_ov101_0229c2ac @ 0x0229c2ac, 0x12 bytes, Thumb
 * func_ov101_0229c29c @ 0x0229c29c, 0xe bytes, Thumb
 * func_ov101_0229c28c @ 0x0229c28c, 0xe bytes, Thumb
 * func_ov101_0229c204 @ 0x0229c204, 0x88 bytes, Thumb
 * func_ov101_0229c180 @ 0x0229c180, 0x84 bytes, Thumb
 */

typedef struct {
    char pad_00[0xb7];
    unsigned char type;
} UnkStruct_0229c5b8;

typedef struct {
    char pad_00[0xb4];
    unsigned char unk_B4;
    char pad_B5[0x20ff];
    char unk_21B4[1];
    char pad_21B5[0x14b];
    char unk_2300[0x3e8];
    char unk_26E8[1];
} UnkStruct_0229c548;

typedef struct {
    char pad_00[0x8C];
    char unk_8C;
    char pad_8D[0x2127];
    char unk_21B4;
} UnkStruct_0229c4ac;

typedef struct {
    char pad_00[0x26e8];
    int value;
} UnkStruct_0229c480;

typedef struct UnkStruct_0229c330 {
    unsigned char pad_00[0xb3];
    unsigned char unk_B3;
} UnkStruct_0229c330;

typedef struct Object Object;

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);
extern int func_ov002_02207d24(void *ptr, int value);
extern void func_ov002_0220a374(void *ptr, int value);
extern void func_ov101_0229cf80(UnkStruct_0229c5b8 *self);
extern void func_ov002_02208c58(char *a, char *b, int c);
extern int func_ov101_0229cd08(void *self, unsigned char b);
extern int func_ov101_0229ccd0(void *self, unsigned char b);
extern void func_ov002_02209874(char *a, char *b);
extern void func_ov002_02209910(char *a, int b, int c);
extern void func_ov002_0220970c(char *a, int b);
extern void func_ov101_0229c6a0(void *);
extern void func_ov002_022096d8(void *, int);
extern void func_0206fc80(unsigned char);
extern void func_0206fc4c(int);
extern unsigned char *func_ov002_022080a0(void *, unsigned char value);
extern void func_ov101_0229c844(void *);
extern int func_0206f9c0(void);
extern int func_ov002_02208d4c(void *, int, int);
extern void func_ov002_02208d30(void *, int);
extern int func_ov101_0229ce38(void *, int);
extern int func_ov002_022088ac(Object *obj);
extern int func_ov002_022088cc(Object *obj);
extern int func_ov002_0220889c(Object *obj);
extern int func_ov002_022088bc(Object *obj);
extern void func_ov002_0220a314(void *ptr);
extern void func_ov002_0220a2b4(unsigned char *);
extern void *func_ov002_0220afdc(void *p);
extern void *func_ov002_0220ba0c(void *p);
extern void *func_ov002_02209ac8(void *p);
extern void *func_ov002_02209cb4(void *p);
extern void func_ov002_02209e38(void *p);
extern void *func_ov002_02207e28(void *p);
extern void *func_ov094_0229a2d0(void *p);
extern void func_ov094_0229bc30(void *p);
extern void *func_ov094_0229afe0(void *p);
extern void *func_ov002_0220826c(void *p);
extern void func_ov002_02207f6c(void *p);
extern unsigned char data_ov101_0229e078[];

void func_ov101_0229c4e0(void *self);
int func_ov101_0229c2ac(int r0, int r1);
void func_ov101_0229c29c(void *self, int value);
void func_ov101_0229c28c(unsigned int *p, unsigned int mask);

void func_ov101_0229c660(void *arg0)
{
    func_ov002_0220a1dc((char *) arg0 + 0x229c);
    func_ov002_02208098(arg0, 0xb);
}

void func_ov101_0229c624(void *self, unsigned char value)
{
    func_ov002_02207d24((char *) self + 0x21b4, 1);
    ((char *) self)[0xb5] = value;
    func_ov002_0220a374((char *) self + 0x229c, 5);
    func_ov002_02208098(self, 0xf);
}

void func_ov101_0229c5dc(unsigned char *base, unsigned char b)
{
    func_ov002_02207d24(base + 0x21b4, 1);
    base[0xb6] = base[0x8d];
    base[0xb5] = b;
    func_ov002_0220a374(base + 0x229c, 6);
    func_ov002_02208098(base, 0x10);
}

void func_ov101_0229c5b8(UnkStruct_0229c5b8 *self)
{
    switch (self->type) {
        case 0:
            func_ov101_0229c4e0((void *) self);
            break;
        case 1:
        default:
            func_ov101_0229cf80(self);
            break;
    }
}

void func_ov101_0229c548(UnkStruct_0229c548 *self, int flag)
{
    int ret1, ret2;

    func_ov002_02208c58(self->unk_2300, self->unk_26E8, 0);
    ret1 = func_ov101_0229cd08(self, self->unk_B4);
    ret2 = func_ov101_0229ccd0(self, self->unk_B4);

    if (flag != 0) {
        func_ov002_02209874(self->unk_2300, self->unk_21B4);
    } else {
        func_ov002_02209910(self->unk_2300, ret1, ret2);
    }

    func_ov002_0220970c(self->unk_2300, 0);
    func_ov002_02208098(self, 0x13);
}

void func_ov101_0229c51c(unsigned char *base)
{
    base[0xb7] = 1;
    func_ov101_0229c6a0(base);
    func_ov002_022096d8(base + 0x2300, 0);
    func_ov002_02208098(base, 0x15);
}

void func_ov101_0229c4e0(void *self)
{
    unsigned char b = *(unsigned char *) ((char *) self + 0xb4);
    func_0206fc80(b);
    func_0206fc4c(1);
    *(unsigned char *) ((char *) self + 0x8c) = 3;
    func_ov002_022080a0(self, 1);
    func_ov002_02207d24((char *) self + 0x21b4, 1);
    func_ov101_0229c844(self);
}

void func_ov101_0229c4ac(UnkStruct_0229c4ac *self)
{
    func_0206fc4c(0);
    self->unk_8C = 3;
    func_ov002_022080a0((void *) self, 1);
    func_ov002_02207d24((void *) (&self->unk_21B4), 1);
    func_ov101_0229c844((void *) self);
}

void func_ov101_0229c480(UnkStruct_0229c480 *arg)
{
    int result = func_0206f9c0();
    func_ov002_02208d4c(&arg->value, result, 0);
    func_ov002_02208d4c(&arg->value, 2, 1);
}

void func_ov101_0229c42c(char *self, int a, int c)
{
    self[0xb4] = (char) a;
    func_ov002_02208d30(self + 0x26e8, 1);

    if (func_ov101_0229ce38(self, a) != 0) {
        func_ov101_0229c480((UnkStruct_0229c480 *) self);
        func_ov101_0229c844(self);
        if (c == 0) {
            func_ov002_02207d24(self + 0x21b4, 1);
        }
        func_ov101_0229c548((UnkStruct_0229c548 *) self, c);
    }
}

void func_ov101_0229c330(UnkStruct_0229c330 *self, Object *obj)
{
    int r4 = self->unk_B3;
    int r6 = 0;
    while (r4 >= 5) {
        r4 -= 5;
        r6++;
    }

    if (func_ov002_022088ac(obj) != 0) {
        if (func_ov002_022088cc(obj) != 0) {
            if (r6 != 0) {
                goto common;
            }
        }
        // fall through to check_r4
    } else {
        goto else_branch;
    }

check_r4:
    if (r4 == 0) {
        self->unk_B3 = self->unk_B3 + 4;
        func_ov101_0229c29c((void *) self, 8);
        goto common;
    } else {
        self->unk_B3 = self->unk_B3 - 1;
        goto common;
    }

else_branch:
    if (func_ov002_0220889c(obj) == 0) {
        goto common;
    }
    if (func_ov002_022088bc(obj) != 0) {
        goto common;
    }
    if (r4 == 4) {
        self->unk_B3 = self->unk_B3 - 4;
        func_ov101_0229c29c((void *) self, 0x10);
        goto common;
    } else {
        self->unk_B3 = self->unk_B3 + 1;
    }

common:
    if (func_ov101_0229c2ac((int) self, 0x18) == 0) {
        if (func_ov002_022088cc(obj) != 0) {
            if (r6 > 0) {
                self->unk_B3 = self->unk_B3 - 5;
            }
        } else if (func_ov002_022088bc(obj) != 0) {
            if (r6 < 2) {
                self->unk_B3 = self->unk_B3 + 5;
            } else {
                self->unk_B3 = 0xf;
                func_ov002_0220a314((char *) self + 0x229c);
            }
        }
    }
}

int func_ov101_0229c2c0(unsigned char *p, int param1)
{
    unsigned char b = p[0xb3];
    func_ov101_0229c28c((unsigned int *) p, 0x18);
    if (param1 == 0) {
        return 0;
    }
    if (func_ov101_0229ce38((void *) p, (unsigned char) p[0xb3]) != 0) {
        func_ov101_0229c330((UnkStruct_0229c330 *) p, (Object *) param1);
    } else {
        if (p[0xb3] == 0xf) {
            if (func_ov002_022088cc((Object *) param1) != 0) {
                p[0xb3] = 0xe;
                func_ov002_0220a2b4(p + 0x229c);
            }
        }
    }
    if (b == p[0xb3]) {
        return 0;
    }
    return 1;
}

int func_ov101_0229c2ac(int r0, int r1)
{
    if ((*(int *) (r0 + 0x94) & r1) != 0) {
        return 1;
    }
    return 0;
}

void func_ov101_0229c29c(void *self, int value)
{
    unsigned int *field = (unsigned int *) ((char *) self + 0x94);
    *field |= value;
}

void func_ov101_0229c28c(unsigned int *p, unsigned int mask)
{
    unsigned int value;
    value = p[0x25];
    value &= ~mask;
    p[0x25] = value;
}

void *func_ov101_0229c204(void *self)
{
    *(void **) self = (void *) data_ov101_0229e078;
    func_ov002_0220afdc((char *) self + 0x2810);
    func_ov002_0220ba0c((char *) self + 0x26f4);
    func_ov002_02209ac8((char *) self + 0x2300);
    func_ov002_02209cb4((char *) self + 0x229c);
    func_ov002_02209e38((char *) self + 0x2284);
    func_ov002_02207e28((char *) self + 0x21b4);
    func_ov094_0229a2d0((char *) self + 0x0b7c);
    func_ov094_0229bc30((char *) self + 0x0b54);
    func_ov094_0229afe0((char *) self + 0xf4);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

void *func_ov101_0229c180(void *self)
{
    *(void **) self = ((char *) data_ov101_0229e078);
    func_ov002_0220afdc((char *) self + 0x2810);
    func_ov002_0220ba0c((char *) self + 0x26f4);
    func_ov002_02209ac8((char *) self + 0x2300);
    func_ov002_02209cb4((char *) self + 0x229c);
    func_ov002_02209e38((char *) self + 0x2284);
    func_ov002_02207e28((char *) self + 0x21b4);
    func_ov094_0229a2d0((char *) self + 0x0b7c);
    func_ov094_0229bc30((char *) self + 0x0b54);
    func_ov094_0229afe0((char *) self + 0xf4);
    func_ov002_0220826c(self);
    return self;
}
