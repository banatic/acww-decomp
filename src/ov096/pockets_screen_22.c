/* pockets_screen_22: 17 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_022a19dc @ 0x022a19dc, 0x4 bytes, Thumb
 * func_ov096_022a19d8 @ 0x022a19d8, 0x4 bytes, Thumb
 * func_ov096_022a19c8 @ 0x022a19c8, 0x10 bytes, Thumb
 * func_ov096_022a192c @ 0x022a192c, 0x9c bytes, Thumb
 * func_ov096_022a18dc @ 0x022a18dc, 0x50 bytes, Thumb
 * func_ov096_022a18a0 @ 0x022a18a0, 0x3c bytes, Thumb
 * func_ov096_022a186c @ 0x022a186c, 0x34 bytes, Thumb
 * func_ov096_022a1838 @ 0x022a1838, 0x34 bytes, Thumb
 * func_ov096_022a17cc @ 0x022a17cc, 0x6c bytes, Thumb
 * func_ov096_022a1794 @ 0x022a1794, 0x38 bytes, Thumb
 * func_ov096_022a1744 @ 0x022a1744, 0x50 bytes, Thumb
 * func_ov096_022a16e4 @ 0x022a16e4, 0x60 bytes, Thumb
 * func_ov096_022a1660 @ 0x022a1660, 0x84 bytes, Thumb
 * func_ov096_022a1610 @ 0x022a1610, 0x50 bytes, Thumb
 * func_ov096_022a15d4 @ 0x022a15d4, 0x3c bytes, Thumb
 * func_ov096_022a1554 @ 0x022a1554, 0x80 bytes, Thumb
 * func_ov096_022a1540 @ 0x022a1540, 0x12 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
} UnkStruct_022a192c;

typedef struct {
    volatile unsigned short unk_00;
    volatile unsigned short unk_02;
} GlobalRegs;

struct UnkStruct_022a18dc {
    char pad_00[0x8c];
    char unk_8C;
};

struct UnkStruct_022a1794 {
    char pad_00[0x98];
    void *unk_98;
};

struct UnkStruct_022a16e4 {
    char pad_00[0x98];
    int unk_98;
};

extern void func_020ee470(void *argument0);
extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern GlobalRegs data_021fbe40; // linked at 0x021fbe40
extern void func_ov090_022993cc(int x, unsigned char b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov096_0229c414(struct UnkStruct_022a18dc *s);
extern void func_ov096_022a1394(void);
extern void func_ov094_0229a204(char *p, int a);
extern void func_ov094_0229a1c0(void *);
extern void func_ov002_02208090(void *, int);
extern int func_ov096_0229c2fc(void *, unsigned int);
extern int func_ov096_022a1384(void *);
extern void func_02002708(int);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov096_0229c2ec(void *, int);
extern int func_ov002_02207f48(struct UnkStruct_022a1794 *self, int a);
extern void func_ov096_0229fb9c(struct UnkStruct_022a1794 *self);
extern int func_ov002_02207d24(void *ptr, int val);
extern void func_ov096_0229ddd8(void *self);
extern void func_ov002_02207f04(void *self, int a, int b, int c, int d);
extern int func_ov002_02207f60(void *self);
extern int func_ov002_02207f3c(void *self, int flag);
extern void func_020027f0(int n);
extern void func_ov096_0229c2dc(void *self, int n);
extern void *func_ov096_0229c4dc(char *);
extern void func_020664a8(void *);
extern void func_0206e230(char *, void *, int, int, int);
extern void func_ov002_0220b53c(char *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_020ee45c(void *self);
extern void func_ov090_022990d0(int arg);
extern void func_ov090_022990c8(int argument0);

int func_ov096_022a18dc(struct UnkStruct_022a18dc *s, int b);
void func_ov096_022a186c(char *self);
void func_ov096_022a1838(void *param);
void func_ov096_022a17cc(void *obj);

int func_ov096_022a19dc(void)
{
    return 1;
}

int func_ov096_022a19d8(void)
{
    return 1;
}

int func_ov096_022a19c8(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

int func_ov096_022a192c(UnkStruct_022a192c *self)
{
    unsigned char f;
    int result;
    int ret;

    func_0206f58c();
    if (func_0206f56c() != 0) {
        f = self->unk_8D;
        if (f == 0 || f == 1 || f == 0xa) {
            return func_ov096_022a18dc((struct UnkStruct_022a18dc *) ((void *) self), 7);
        }
    }

    f = self->unk_8D;
    if (f != 0 && f != 0xa) {
        return 0;
    }

    result = -1;
    ret = func_0206fe60();
    if (ret != 0) {
        result = func_ov090_022990e0();
    } else {
        unsigned short val = data_021fbe40.unk_02;
        if (val & 0x800) {
            result = 7;
        } else if (val & 0x400) {
            result = 5;
        } else if (val & 0x4) {
            result = 4;
        }
    }

    return func_ov096_022a18dc((struct UnkStruct_022a18dc *) ((void *) self), result);
}

int func_ov096_022a18dc(struct UnkStruct_022a18dc *s, int b)
{
    int x;

    x = func_020ee45c((void *) s);
    if (b == -1) {
        goto fail;
    }
    if (b == 0) {
        goto fail;
    }

    func_ov090_022993cc(x, (unsigned char) b);
    s->unk_8C = 5;
    func_ov002_022080a0((void *) (s), 1);
    if (b != 7) {
        func_ov096_0229c414(s);
    }
    func_ov096_0229c2dc((void *) s, 0x80);
    return 1;

fail:
    return 0;
}

void func_ov096_022a18a0(char *p)
{
    func_ov096_022a1394();
    func_ov094_0229a204(p + 0xde0, 1);
    func_ov002_02208090((void *) p, 1);
    if (func_ov096_0229c2fc((void *) p, 0x80000) == 0) {
        func_ov096_022a186c(p);
    }
}

void func_ov096_022a186c(char *self)
{
    func_ov094_0229a1c0(self + 0xde0);
    func_ov002_02208090(self, 2);
    if (func_ov096_0229c2fc(self, 0x00080000) == 0) {
        func_ov096_022a1838(self);
    }
}

void func_ov096_022a1838(void *param)
{
    func_ov096_022a1384(param);
    func_ov002_02208090(param, 3);
    if (func_ov096_0229c2fc(param, 0x00080000) == 0) {
        func_ov096_022a17cc(param);
        func_ov096_0229c2dc(param, 0x00080000);
    }
}

void func_ov096_022a17cc(void *obj)
{
    func_ov094_0229ad20((char *) obj + 0x358);
    func_ov094_0229b2b0((char *) obj + 0xDB8);
    func_ov002_02207f20(obj, 8, 3, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(obj, 6, 0, 0);
    func_ov002_02208090(obj, 4);
    func_ov096_0229c2ec(obj, 1);
    func_ov096_0229c2ec(obj, 2);
    *(void **) ((char *) obj + 0x98) = (void *) func_ov002_02207f60(obj);
}

void func_ov096_022a1794(struct UnkStruct_022a1794 *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0((void *) (self), 2);
        func_ov096_0229fb9c(self);
    }
    func_ov002_02207e80((void *) self, 6, 0, 0);
    self->unk_98 = (void *) func_ov002_02207f60((void *) self);
}

void func_ov096_022a1744(void *self)
{
    func_ov002_02207d24((char *) self + 0x2418, 1);
    func_ov096_0229ddd8(self);
    func_ov002_02207f04(self, 8, 0, 0, 0x30);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 6);
    *(int *) ((char *) self + 0x98) = func_ov002_02207f60(self);
}

void func_ov096_022a16e4(struct UnkStruct_022a16e4 *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(6);
        func_ov096_0229c2dc(self, 2);
        if (func_ov096_0229c2fc(self, 0x80) != 0) {
            func_ov002_02208090(self, 7);
        } else {
            func_ov002_022080a0((void *) (self), 5);
            func_ov096_0229c2dc(self, 1);
        }
    } else {
        func_ov002_02207e80(self, 6, 0, 0);
    }
    self->unk_98 = func_ov002_02207f60(self);
}

void func_ov096_022a1660(char *self)
{
    int zero = 0;
    void *r4;

    r4 = func_ov096_0229c4dc(self);
    func_020664a8(r4);
    func_0206e230(self + 0x2a74, r4, 3, 4, 1);
    func_ov002_02207f20((void *) self, 3, zero, zero, 0x30);
    func_02002708(3);
    func_ov002_02207e80((void *) self, 3, zero, zero);
    func_02002708(4);
    func_ov002_02207e80((void *) self, 4, zero, zero);
    func_ov002_02208090((void *) self, 8);
    func_ov002_0220b53c(self + 0x2d9c, 0x88);
    func_ov096_0229c2ec((void *) self, 0x100);
}

void func_ov096_022a1610(void *p)
{
    if (func_ov002_02207f48((struct UnkStruct_022a1794 *) p, 0) != 0) {
        func_ov002_022080a0((void *) (p), 2);
        if (func_0206fe60() != 0) {
            func_ov002_02208098((void *) (p), 7);
        } else {
            func_ov002_02208098((void *) (p), 0x17);
        }
    } else {
        func_ov002_02207e80(p, 3, 0, 0);
        func_ov002_02207e80(p, 4, 0, 0);
    }
}

void func_ov096_022a15d4(int param)
{
    int local;
    local = 0x30;
    func_ov002_02207f04((void *) param, 3, 0, 0, local);
    func_ov002_02207e80((void *) param, 3, 0, 0);
    func_ov002_02207e80((void *) param, 4, 0, 0);
    func_ov002_02208090((void *) param, 0xa);
}

void func_ov096_022a1554(void *self)
{
    int r4;
    if (func_ov002_02207f3c(self, 0)) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov096_0229c2dc(self, 0x100);
        r4 = func_020ee45c(self);
        if (func_ov096_0229c2fc(self, 0x20000)) {
            func_ov002_022080a0((void *) (self), 5);
            func_ov096_0229c2dc(self, 1);
        } else {
            func_ov090_022990d0(r4);
            func_ov096_022a18a0((char *) self);
        }
    } else {
        func_ov002_02207e80(self, 3, 0, 0);
        func_ov002_02207e80(self, 4, 0, 0);
    }
}

void func_ov096_022a1540(void *argument0)
{

    func_ov090_022990c8(func_020ee45c(argument0));
}
