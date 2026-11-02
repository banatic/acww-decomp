/* soft_keyboard: 21 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_0229c420 @ 0x0229c420, 0x28 bytes, Thumb
 * func_ov095_0229c22c @ 0x0229c22c, 0x1f4 bytes, Thumb
 * func_ov095_0229c208 @ 0x0229c208, 0x22 bytes, Thumb
 * func_ov095_0229c1c4 @ 0x0229c1c4, 0x44 bytes, Thumb
 * func_ov095_0229c178 @ 0x0229c178, 0x4c bytes, Thumb
 * func_ov095_0229c134 @ 0x0229c134, 0x44 bytes, Thumb
 * func_ov095_0229c104 @ 0x0229c104, 0x2e bytes, Thumb
 * func_ov095_0229c084 @ 0x0229c084, 0x80 bytes, Thumb
 * func_ov095_0229c05c @ 0x0229c05c, 0x28 bytes, Thumb
 * func_ov095_0229c050 @ 0x0229c050, 0xc bytes, Thumb
 * func_ov095_0229c01c @ 0x0229c01c, 0x34 bytes, Thumb
 * func_ov095_0229c000 @ 0x0229c000, 0x1c bytes, Thumb
 * func_ov095_0229bfd8 @ 0x0229bfd8, 0x28 bytes, Thumb
 * func_ov095_0229bf7c @ 0x0229bf7c, 0x5c bytes, Thumb
 * func_ov095_0229bf70 @ 0x0229bf70, 0xc bytes, Thumb
 * func_ov095_0229bf48 @ 0x0229bf48, 0x28 bytes, Thumb
 * func_ov095_0229bf3c @ 0x0229bf3c, 0xc bytes, Thumb
 * func_ov095_0229bf0c @ 0x0229bf0c, 0x30 bytes, Thumb
 * func_ov095_0229bee4 @ 0x0229bee4, 0x28 bytes, Thumb
 * func_ov095_0229bed8 @ 0x0229bed8, 0xc bytes, Thumb
 * func_ov095_0229bebc @ 0x0229bebc, 0x1c bytes, Thumb
 */

struct Struct_ov095_0229c420 {
    char pad_00[0x16];
    volatile unsigned char unk_16;
};

typedef struct UnkStruct_0229c22c UnkStruct_0229c22c;

struct UnkStruct_0229c22c {
    unsigned char pad_00[0x16];
    unsigned char unk_16;
    unsigned char pad_17[0x1b - 0x17];
    unsigned char unk_1B;
    unsigned char pad_1C[0x48 - 0x1c];
    unsigned char unk_48[1];
    unsigned char pad_49[0x2308 - 0x49];
    unsigned char unk_2308[1];
    unsigned char pad_2309[0x2668 - 0x2309];
    unsigned char unk_2668[1];
};

struct UnkStruct_0229c208 {
    char pad_00[0x1b];
    unsigned char unk_1B;
};

typedef struct {
    unsigned char pad_00[0x1b];
    unsigned char unk_1B;
} Struct_ov095_0229c178;

struct UnkStruct_0229c084 {
    unsigned char pad_00[0x14];
    unsigned short unk_14;
    unsigned char unk_16;
    unsigned char unk_17;
    unsigned char unk_18;
    unsigned char unk_19;
    unsigned char unk_1A;
    unsigned char unk_1B;
    unsigned char pad_1C[0x20 - 0x1c];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    int unk_30;
    unsigned char pad_34[0x42 - 0x34];
    unsigned char unk_42;
    unsigned char pad_43[0x44 - 0x43];
    void *unk_44;
};

typedef struct UnkStruct_0229bf48 {
    char pad_00[0x1c];
    unsigned char unk_1C;
} UnkStruct_0229bf48;

typedef struct {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    unsigned char pad_1D[0x23];
    unsigned char unk_40;
} UnkStruct_0229bf0c;

extern int func_0206f608(void);
extern int func_0206f5e4(int value);
extern void func_0206f5d8(int, int);
extern int func_ov095_022999b0(void *p, int n);
extern int func_02002d14(void *, void *, unsigned int, int, int, int);
extern int func_02064af4(const void *, void *, unsigned int);
extern unsigned char *func_02064b2c(const void *, void *, int, int);
extern void MI_CpuCopy8(void *, void *, unsigned int);
extern void func_020e993c(void *, void *);
extern int func_020b9c10(void *, void *, unsigned int, int, int, int);
extern void func_ov095_0229cef4(UnkStruct_0229c22c *, int);
extern void func_ov095_0229ce84(UnkStruct_0229c22c *, int);
extern void func_ov095_0229b3ec(UnkStruct_0229c22c *);
extern void func_ov095_0229cd30(UnkStruct_0229c22c *);
extern void *data_021fbe94;
extern const void *const data_ov095_0229e5f8[];
extern const void *const data_ov095_0229e61c[];
extern const void *const data_ov095_0229e640[];
extern unsigned char data_ov095_0229ee74[];
extern void func_ov095_022999a0(void *p, int n);
extern void func_ov095_022999a8(void *a, int b);
extern int func_020984e8(void);
extern int func_02099870(int object);
extern int func_020950c0(void *argument0);
extern void func_0200458c(int arg);
extern int data_ov095_0229e6b4;
extern int data_ov095_0229e6e4;
extern void func_020b9ccc(void *);
extern void func_0206f5fc(unsigned char);
extern int func_02002c6c(void *a, int b, int c, int d, int e, int f);
extern unsigned char data_ov095_0229ee5c[];
extern int func_02002b40(void *ptr, int a, int b, int c);
extern int func_020b9bbc(void *a, void *b, unsigned int bank, int d, int e);
extern void func_ov095_0229cce0(UnkStruct_0229bf48 *self);

void func_ov095_0229c22c(UnkStruct_0229c22c *self, int state, unsigned int p2, int p3);
void func_ov095_0229bf7c(void *p, unsigned int q);
void func_ov095_0229bf70(int a);

void func_ov095_0229c420(struct Struct_ov095_0229c420 *self, int arg2)
{
    self->unk_16 = (unsigned char) func_0206f608();
    func_ov095_0229c22c((UnkStruct_0229c22c *) self, func_0206f5e4(self->unk_16), arg2, 0);
}

void func_ov095_0229c22c(UnkStruct_0229c22c *self, int state, unsigned int p2, int p3)
{
    void *v;
    const void *ptr;
    unsigned char *ret;

    if (state == 9) {
        state = func_0206f5e4(self->unk_16);
    }
    if (state == 3 && func_ov095_022999b0(self, 0x20)) {
        func_0206f5d8(self->unk_16, 2);
    } else {
        func_0206f5d8(self->unk_16, state);
    }

    v = data_021fbe94;

    if (p3 == 0) {
        func_02002d14((void *) data_ov095_0229ee74, v, p2, 1, 1, 4);
        func_02002d14((void *) data_ov095_0229ee74, v, p2, 1, 7, 7);
        func_02002d14((void *) data_ov095_0229ee74, v, p2, 1, 9, 9);
    }

    if (self->unk_1B == state && p3 != 0) {
        goto done;
    }

    ptr = data_ov095_0229e5f8[state];
    func_02064af4(ptr, self->unk_48, 0x22c0);

    if (func_ov095_022999b0((void *) self, 4) != 0) {
        ptr = data_ov095_0229e61c[state];
    } else {
        ptr = data_ov095_0229e640[state];
    }

    ret = func_02064b2c(ptr, v, -4, 0);
    MI_CpuCopy8(ret + 0x240, self->unk_2668, 0x380);
    func_ov095_0229bf70((int) self);
    func_020e993c(v, ret);
    func_020b9c10(self->unk_2308, self->unk_48, p2, 0x1ea, 0x1ea, 0x2ff);

    self->unk_1B = state;

    switch (self->unk_1B) {
        case 0:
            func_ov095_0229cef4(self, 1);
            func_ov095_0229ce84(self, 2);
            break;
        case 1:
            func_ov095_0229ce84(self, 1);
            func_ov095_0229cef4(self, 2);
            break;
        case 2:
        case 3:
            func_ov095_0229cef4(self, 8);
            func_ov095_0229ce84(self, 9);
            func_ov095_0229ce84(self, 10);
            func_ov095_0229ce84(self, 7);
            func_ov095_0229ce84(self, 13);
            break;
        case 4:
            func_ov095_0229ce84(self, 8);
            func_ov095_0229cef4(self, 9);
            func_ov095_0229ce84(self, 10);
            func_ov095_0229cef4(self, 7);
            func_ov095_0229cef4(self, 13);
            break;
        case 5:
            func_ov095_0229ce84(self, 8);
            func_ov095_0229ce84(self, 9);
            func_ov095_0229cef4(self, 10);
            func_ov095_0229cef4(self, 7);
            func_ov095_0229cef4(self, 13);
            break;
        case 6:
            break;
    }

    func_ov095_0229b3ec(self);

done:
    func_ov095_0229cd30(self);
}

void func_ov095_0229c208(struct UnkStruct_0229c208 *param0, unsigned int param1)
{
    func_ov095_0229c22c((UnkStruct_0229c22c *) param0, param0->unk_1B, param1, 0);
    func_ov095_0229bf7c((void *) param0, param1);
}

void func_ov095_0229c1c4(void *obj, int id, int b)
{
    switch (id) {
        case 0x107:
            ((unsigned char *) obj)[0x16] = 4;
            break;
        case 0x108:
            ((unsigned char *) obj)[0x16] = 1;
            break;
        case 0x109:
            ((unsigned char *) obj)[0x16] = 2;
            break;
    }
    func_ov095_0229c22c((UnkStruct_0229c22c *) obj, 9, b, 1);
}

void func_ov095_0229c178(Struct_ov095_0229c178 *p, int param)
{
    if (func_ov095_022999b0(p, 0x20) != 0) {
        p->unk_1B = 2;
        func_ov095_022999a0(p, 0x20);
    }
    switch (p->unk_1B) {
        case 2:
            func_ov095_0229c22c((UnkStruct_0229c22c *) p, 3, param, 1);
            break;
        case 3:
            func_ov095_0229c22c((UnkStruct_0229c22c *) p, 2, param, 1);
            break;
        default:
            break;
    }
}

void func_ov095_0229c134(void *a, void *b)
{
    if (func_ov095_022999b0(a, 0x20)) {
        func_ov095_022999a0(a, 0x20);
        func_ov095_0229c22c((UnkStruct_0229c22c *) a, 2, (unsigned int) b, 1);
    } else {
        func_ov095_022999a8(a, 0x20);
        func_ov095_0229c22c((UnkStruct_0229c22c *) a, 3, (unsigned int) b, 1);
    }
}

void func_ov095_0229c104(void *a, int b)
{
    if (func_ov095_022999b0(a, 0x20)) {
        func_ov095_022999a0(a, 0x20);
        func_ov095_0229c22c((UnkStruct_0229c22c *) a, 2, b, 1);
    }
}

void func_ov095_0229c084(struct UnkStruct_0229c084 *obj, int param2)
{
    int local;
    int object;

    obj->unk_20 = 0;
    obj->unk_1B = 9;
    obj->unk_24 = -1;
    obj->unk_14 = 0;
    obj->unk_17 = 0xFF;
    obj->unk_18 = 0;
    obj->unk_28 = -1;
    obj->unk_2C = 0x64;
    obj->unk_30 = 0x64;
    func_ov095_0229b3ec((UnkStruct_0229c22c *) obj);
    if (param2 == 0) {
        func_ov095_022999a8(obj, 4);
        obj->unk_44 = (void *) &data_ov095_0229e6b4;
    } else {
        obj->unk_44 = (void *) &data_ov095_0229e6e4;
    }
    obj->unk_42 = (unsigned char) param2;
    obj->unk_19 = 0x0c;
    obj->unk_1A = 0x0c;
    obj->unk_16 = 0x04;
    if ((object = func_020984e8()) != 0) {

        if (func_020950c0((void *) func_02099870(object)) == 0) {
            func_0200458c(0);
            return;
        }
    }
    func_0200458c(1);
}

void func_ov095_0229c05c(void *r0)
{
    func_020b9ccc((char *) r0 + 0x2308);
    func_020b9ccc((char *) r0 + 0x232c);
    func_0206f5fc(*(unsigned char *) ((char *) r0 + 0x16));
}

void func_ov095_0229c050(int a)
{
    func_ov095_022999a8((void *) a, 8);
}

int func_ov095_0229c01c(int a, int b)
{
    return func_02002c6c((void *) data_ov095_0229ee5c, (*(int *) &data_021fbe94), b, 0x13d, 0x1eb, 0x1f0);
}

int func_ov095_0229c000(int arg0, int arg1)
{
    return func_02064af4((const void *) arg1, (void *) (arg0 + 0x2428), 0x800);
}

void func_ov095_0229bfd8(void *base, int arg)
{
    func_02002b40((char *) base + 0x2428, arg, 0x800, 0);
    func_ov095_022999a0(base, 1);
}

void func_ov095_0229bf7c(void *p, unsigned int q)
{
    if (func_ov095_022999b0(p, 1)) {
        if (func_020b9bbc((char *) p + 0x232c, (char *) p + 0x2428, q, 0x800, 0)) {
            func_ov095_022999a0(p, 1);
        }
    }
    func_ov095_022999a0(p, 2);
    func_ov095_022999a0(p, 0x200);
}

void func_ov095_0229bf70(int a)
{
    func_ov095_022999a8((void *) a, 1);
}

int func_ov095_0229bf48(UnkStruct_0229bf48 *self)
{
    if (self->unk_1C != 0) {
        self->unk_1C--;
        if (self->unk_1C >= 4) {
            return 1;
        } else {
            if (self->unk_1C == 0) {
                func_ov095_0229cce0(self);
            }
        }
    }
    return 0;
}

void func_ov095_0229bf3c(void *param0)
{
    *(unsigned char *) ((char *) param0 + 0x1c) = 5;
    *(unsigned char *) ((char *) param0 + 0x40) = 0xd;
}

int func_ov095_0229bf0c(UnkStruct_0229bf0c *p)
{
    unsigned char v = p->unk_1C;
    if (v > 1) {
        p->unk_1C = v - 1;
    }

    if (p->unk_40) {
        p->unk_40--;
    } else {
        p->unk_40 = 1;
        return 1;
    }
    return 0;
}

void func_ov095_0229bee4(void *p)
{
    func_ov095_0229cef4((UnkStruct_0229c22c *) p, 6);
    func_ov095_0229cef4((UnkStruct_0229c22c *) p, 3);
    func_ov095_0229cef4((UnkStruct_0229c22c *) p, 4);
    func_ov095_0229cef4((UnkStruct_0229c22c *) p, 5);
}

void func_ov095_0229bed8(void *receiver, int value)
{
    func_ov095_0229ce84((UnkStruct_0229c22c *) ((int) receiver), 6);
}

int func_ov095_0229bebc(int arg0, int x)
{
    if (x >= 0x100 && x < 0x124) {
        return 1;
    }
    return 0;
}
