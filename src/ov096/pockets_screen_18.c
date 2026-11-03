/* pockets_screen_18: 16 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_022a0654 @ 0x022a0654, 0x34 bytes, Thumb
 * func_ov096_022a062c @ 0x022a062c, 0x28 bytes, Thumb
 * func_ov096_022a05fc @ 0x022a05fc, 0x30 bytes, Thumb
 * func_ov096_022a05d0 @ 0x022a05d0, 0x2c bytes, Thumb
 * func_ov096_022a053c @ 0x022a053c, 0x94 bytes, Thumb
 * func_ov096_022a04f4 @ 0x022a04f4, 0x48 bytes, Thumb
 * func_ov096_022a04a4 @ 0x022a04a4, 0x50 bytes, Thumb
 * func_ov096_022a03e4 @ 0x022a03e4, 0xc0 bytes, Thumb
 * func_ov096_022a03c4 @ 0x022a03c4, 0x20 bytes, Thumb
 * func_ov096_022a033c @ 0x022a033c, 0x88 bytes, Thumb
 * func_ov096_022a02ec @ 0x022a02ec, 0x50 bytes, Thumb
 * func_ov096_022a0274 @ 0x022a0274, 0x78 bytes, Thumb
 * func_ov096_022a0218 @ 0x022a0218, 0x5c bytes, Thumb
 * func_ov096_022a01dc @ 0x022a01dc, 0x3c bytes, Thumb
 * func_ov096_022a018c @ 0x022a018c, 0x50 bytes, Thumb
 * func_ov096_022a0170 @ 0x022a0170, 0x1a bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xb5];
    unsigned char b5;
    unsigned char pad_B6[0x244a];
    unsigned char data[1];
} UnkStruct_022a0654;

typedef struct UnkStruct_022a053c UnkStruct_022a053c;

struct UnkStruct_022a053c {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x20];
    unsigned short unk_AE;
    char pad_B0[5];
    unsigned char unk_B5;
    char pad_B6;
    unsigned char unk_B7;
    char pad_B8;
    unsigned char unk_B9;
    char pad_BA[0x2446];
    char unk_2500;
};

typedef struct UnkStruct_022a04f4 {
    char pad_00[0xB7];
    unsigned char byte_at_B7;
} UnkStruct_022a04f4;

struct GFlag {
    unsigned char pad_00[2];
    unsigned short unk_02;
};

struct UnkStruct_022a0274 {
    char pad_00[0xa4];
    int a4;
    int a8;
    char pad_AC[8];
    unsigned char b4;
};

typedef struct {
    unsigned char pad_00[0xae];
    unsigned short unk_AE;
    unsigned char pad_B0[4];
    unsigned char unk_B4;
    unsigned char pad_B5[4];
    unsigned char unk_B9;
} FuncOv096Struct;

extern int func_0208e484(void *ptr);
extern int func_ov096_022a18dc(UnkStruct_022a0654 *self, int arg);
extern void func_ov096_0229dbe8(UnkStruct_022a0654 *self);
extern void func_ov096_0229dc28(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov096_0229f970(void *a, unsigned char b);
extern int func_ov002_02209f9c(void *a);
extern int func_ov096_0229ea5c(void *);
extern int func_ov096_0229e79c(UnkStruct_022a053c *self, int value);
extern void func_ov096_0229e9f8(UnkStruct_022a053c *self, unsigned short a, int b);
extern unsigned char *func_ov096_0229f90c(UnkStruct_022a053c *self, unsigned char a, int b);
extern void func_ov096_0229c2dc(UnkStruct_022a053c *self, int a);
extern void func_ov096_0229eb14(UnkStruct_022a053c *self);
extern void func_ov094_022999d8(void);
extern int func_ov002_02209f70(void *p);
extern void func_ov096_0229e7c4(UnkStruct_022a04f4 *p, unsigned char b);
extern void func_ov096_0229c2ec(UnkStruct_022a04f4 *p, int n);
extern void func_ov094_022999c0(void);
extern int func_0206f56c(void);
extern void func_ov096_0229c4ec(unsigned char *p);
extern void func_ov096_0229c514(unsigned char *p);
extern int func_0208e4bc(unsigned char *p);
extern int func_ov002_0220b5ec(unsigned char *p, int arg);
extern int func_ov002_0220b59c(unsigned char *p, int arg);
extern void func_ov002_0220a0b4(unsigned char *p, int a, int b);
extern void func_ov002_0220a374(unsigned char *p, int arg);
extern int func_ov002_02208014(void *receiver);
extern void func_ov096_0229ddd8(unsigned char *p);
extern void func_ov002_0220a1dc(unsigned char *p);
extern unsigned short data_021fbe40[2];
extern void func_ov096_0229d16c(void *p);
extern int func_ov096_0229fb84(void *p);
extern int func_ov002_02208008(void *p);
extern int func_ov002_02209044(unsigned char *p, int a, unsigned char *q, int b);
extern void func_ov096_0229dd44(void *p);
extern void func_ov002_022090b0(void *a, unsigned char b);
extern unsigned char func_ov002_02208a8c(void *a, unsigned char b, unsigned char c);
extern int func_ov002_02209d8c(char *p);
extern int func_ov096_0229f800(void *p, unsigned char b);
extern int func_ov096_0229c2fc(void *p, int n);
extern int func_ov096_0229f290(void *p, unsigned char b);
extern int func_ov096_0229f200(void *p, unsigned char b);
extern void func_ov096_0229ea34(void *p);
extern void func_ov096_0229e898(void *self, unsigned char a, int b);
extern unsigned char *func_ov096_0229f8cc(void *self, unsigned char b4, unsigned char b9, unsigned short ae, int zero);
extern void func_ov096_0229fb9c(void *self);
extern int func_0206fe54(void);
extern void func_ov096_0229dc7c(int);
extern int func_ov002_02208e28(int);
extern void func_ov096_0229dc48(int);
extern int func_ov002_0220909c(int);
extern void func_ov002_022096d8(int, int);
extern int func_ov002_02207d24(int, int);

void func_ov096_022a0218(FuncOv096Struct *self);

void func_ov096_022a0654(UnkStruct_022a0654 *self)
{
    if (func_0208e484(&self->data[0]) != 0) {
        if (func_ov096_022a18dc(self, self->b5 - 0x19) == 0) {
            func_ov096_0229dbe8(self);
        }
    }
}

void func_ov096_022a062c(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0x2500)) {
        func_ov096_0229dc28(arg0);
        func_ov002_02208098((void *) (arg0), 0xa);
    }
}

void func_ov096_022a05fc(void *self)
{
    if (func_ov002_02209f9c((char *) self + 0x2500)) {
        func_ov096_0229f970(self, *(unsigned char *) ((char *) self + 0xb5));
        func_ov002_02208098((void *) (self), 0x13);
    }
}

int func_ov096_022a05d0(char *self)
{
    if (func_0208e484(self + 0x2500)) {
        func_ov002_02208098((void *) (self), *(unsigned char *) (self + 0xba));
    }
    return func_ov096_0229ea5c(self);
}

void func_ov096_022a053c(UnkStruct_022a053c *self)
{
    if (func_ov002_02209f9c((void *) (&self->unk_2500)) == 0) {
        if (self->unk_B5 == self->unk_B7) {
            func_ov096_0229e79c(self, self->unk_B7);
            if (func_ov096_0229c2fc((void *) self, 0x2000) != 0) {
                func_ov096_0229e9f8(self, self->unk_AE, 0);
                func_ov096_0229f90c(self, self->unk_B9, 4);
                func_ov096_0229c2dc(self, 0x2000);
            }
        } else {
            func_ov096_0229f90c(self, self->unk_B7, 4);
        }
        if (self->unk_8D == 0x14) {
            func_ov096_0229eb14(self);
            ((void) ((int) func_ov002_02208098((void *) (self), 0xa)), func_ov094_022999d8());
        }
    } else {
        func_ov096_0229ea5c((void *) self);
    }
}

void func_ov096_022a04f4(UnkStruct_022a04f4 *obj)
{
    if (func_ov002_02209f70((char *) obj + 0x2500) == 0) {
        func_ov096_0229e7c4(obj, obj->byte_at_B7);
        func_ov096_0229c2ec(obj, 0x40);
        func_ov002_02208098((void *) (obj), 0x16);
        func_ov096_0229eb14((UnkStruct_022a053c *) obj);
    } else {
        func_ov002_02208098((void *) (obj), 0xA);
    }
}

void func_ov096_022a04a4(unsigned char *p)
{
    if (func_0208e484((void *) (p + 0x2500))) {
        func_ov002_02208098((void *) (p), p[0xBA]);
    }
    if (func_ov002_02209f9c((void *) (p + 0x2500))) {
        if (func_ov096_0229c2fc((void *) p, 0x40)) {
            func_ov096_0229c2dc((UnkStruct_022a053c *) p, 0x40);
            func_ov094_022999c0();
        }
        func_ov096_0229ea5c((void *) p);
    }
}

void func_ov096_022a03e4(unsigned char *self)
{
    int a, b, v1, v2, flags;

    a = func_0206f56c();
    if (a != 0) {
        func_ov096_0229c4ec(self);
        return;
    }

    b = func_0206f56c();
    if (b != 0) {
        func_ov096_0229c514(self);
        func_ov096_0229c2ec((UnkStruct_022a04f4 *) self, 0x20000);
        return;
    }

    if (func_0208e4bc(self + 0x2500) == 0) {
        v1 = func_ov002_0220b5ec(self + 0x2d9c, 1);
        v2 = func_ov002_0220b59c(self + 0x2d9c, 1);
        func_ov002_0220a0b4(self + 0x2500, v1, v2);
        func_ov002_0220a374(self + 0x2500, 1);
    }

    if (func_ov002_02208014(self)) {
        func_ov096_0229ddd8(self);
        func_ov002_02208098((void *) (self), 7);
        return;
    }

    flags = data_021fbe40[1];
    if ((flags & 1) != 0 || (flags & 2) != 0) {
        func_ov002_0220a1dc(self + 0x2500);
        func_ov002_02208098((void *) (self), 0x18);
    }
}

void func_ov096_022a03c4(int r0)
{
    if (func_0208e484((void *) (r0 + 0x2500)) != 0) {
        func_ov096_0229c514((unsigned char *) r0);
    }
}

void func_ov096_022a033c(unsigned char *p)
{
    if (func_0206f56c()) {
        func_ov096_0229d16c(p);
        return;
    }
    if (func_ov002_02208014(p)) {
        func_ov096_0229fb84(p);
        return;
    }
    if (func_ov002_02209044(p + 0x2564, func_ov002_02208008(p), p + 0xbc, 0)) {
        func_ov096_0229dd44(p);
    }
    {
        unsigned short flags = (*(struct GFlag *) data_021fbe40).unk_02;
        if ((flags & 1) != 0) {
            func_ov002_0220a1dc((unsigned char *) (p + 0x2500));
            func_ov002_02208098((void *) (p), 0x1a);
        } else if ((flags & 2) != 0) {
            func_ov096_0229d16c(p);
        }
    }
}

void func_ov096_022a02ec(char *self)
{
    if (func_0208e484(self + 0x2500)) {
        func_ov002_022090b0(self + 0x2564, *(unsigned char *) (self + 0xbc));
        *(unsigned char *) (self + 0xbe) =
            func_ov002_02208a8c(self + 0x2564, *(unsigned char *) (self + 0xbd), *(unsigned char *) (self + 0xbc));
        func_ov002_02208098((void *) (self), 0x23);
    }
}

void func_ov096_022a0274(struct UnkStruct_022a0274 *p)
{
    if (func_ov002_02209d8c((char *) p + 0x24e8) != 0) {
        if (func_ov096_0229f800(p, p->b4) != 0 || func_ov096_0229c2fc(p, 0x2000) != 0) {
            p->a4 = func_ov096_0229f290(p, p->b4);
            p->a8 = func_ov096_0229f200(p, p->b4);
            func_ov002_02208098((void *) (p), 0x1c);
            return;
        } else {
            func_ov096_022a0218((FuncOv096Struct *) p);
            return;
        }
    } else {
        func_ov096_0229ea34(p);
        return;
    }
}

void func_ov096_022a0218(FuncOv096Struct *self)
{
    func_ov096_0229e898(self, self->unk_B4, 1);
    if (func_ov096_0229c2fc(self, 0x2000) != 0) {
        func_ov096_0229f8cc(self, self->unk_B4, self->unk_B9, self->unk_AE, 0);
        func_ov096_0229c2dc((UnkStruct_022a053c *) self, 0x2000);
    } else {
        func_ov094_022999d8();
        func_ov096_0229fb9c(self);
    }
}

void func_ov096_022a01dc(int r0)
{
    if (func_ov002_02208e28(r0 + 0x2564) != 0) {
        if (func_0206fe54() != 0) {
            func_ov096_0229dc7c(r0);
            func_ov002_02208098((void *) (r0), 0xd);
        } else {
            func_ov002_02208098((void *) (r0), 4);
        }
    }
}

int func_ov096_022a018c(int r0)
{
    int r4 = r0;
    if (func_ov002_0220909c(r4 + 0x2564) != 0) {
        func_ov002_022096d8(r4 + 0x2564, 0);
        func_ov002_02207d24(r4 + 0x2418, 1);
        if (func_0208e4bc((unsigned char *) (r4 + 0x2500)) != 0) {
            func_ov096_0229dc48(r4);
        }
        return 1;
    }
    return 0;
}

void func_ov096_022a0170(int param)
{
    int r4 = param;
    if (func_ov096_022a018c(param) != 0) {
        func_ov002_02208098((void *) (r4), 0x1f);
    }
}
