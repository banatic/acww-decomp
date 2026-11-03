/* fish_catalog_5: 12 functions, module ov115
 * mwccarm 1.2/base -O4,s
 * func_ov115_0229e5b8 @ 0x0229e5b8, 0x4 bytes, Thumb
 * func_ov115_0229e5b4 @ 0x0229e5b4, 0x4 bytes, Thumb
 * func_ov115_0229e5a4 @ 0x0229e5a4, 0x10 bytes, Thumb
 * func_ov115_0229e50c @ 0x0229e50c, 0x98 bytes, Thumb
 * func_ov115_0229e4cc @ 0x0229e4cc, 0x3e bytes, Thumb
 * func_ov115_0229e47c @ 0x0229e47c, 0x50 bytes, Thumb
 * func_ov115_0229e454 @ 0x0229e454, 0x28 bytes, Thumb
 * func_ov115_0229e41c @ 0x0229e41c, 0x38 bytes, Thumb
 * func_ov115_0229e3e4 @ 0x0229e3e4, 0x36 bytes, Thumb
 * func_ov115_0229e3a8 @ 0x0229e3a8, 0x3c bytes, Thumb
 * func_ov115_0229e384 @ 0x0229e384, 0x24 bytes, Thumb
 * func_ov115_0229e36c @ 0x0229e36c, 0x16 bytes, Thumb
 */

typedef struct {
    char pad[0x8d];
    unsigned char flag;
} UnkStruct_0229e50c;

typedef struct {
    unsigned char pad_00[0x1428];
    unsigned short unk_1428;
} Func225E384Struct;

extern void func_020ee470(void *argument0);
extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern struct {
    char pad[2];
    unsigned short field;
} data_021fbe40;
extern int func_020ee45c(void *self);
extern void func_ov090_022993cc(int a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov115_0229e2e0(void);
extern void func_ov115_0229e2c8(void *);
extern void func_ov115_0229e2b0(void *);
extern void func_02002708(int);
extern void func_ov115_0229dda8(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern int func_ov002_02207f48(void *, int kind);
extern void func_ov115_0229df6c(int arg);
extern void func_ov115_0229deb4(void *);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov114_0229c8b4(void *);
extern int func_ov002_02207f3c(int, int);
extern void func_020027f0(int);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);
extern void func_ov114_0229d8d0(void *p, int a, int b, int c, int d);
extern void func_ov114_0229d8ac(void *p);
extern void func_ov115_0229df50(void *p);

int func_ov115_0229e4cc(void *self, int type);
void func_ov115_0229e3a8(void *p);

int func_ov115_0229e5b8(void)
{
    return 1;
}

int func_ov115_0229e5b4(void)
{
    return 1;
}

int func_ov115_0229e5a4(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

int func_ov115_0229e50c(UnkStruct_0229e50c *p)
{
    volatile int unused;
    int ret;

    func_0206f58c();
    if (func_0206f56c() != 0) {
        return func_ov115_0229e4cc(p, 7);
    }
    if (p->flag != 0 && p->flag != 2) {
        return 0;
    }

    ret = -1;
    if (func_0206fe60() != 0) {
        ret = func_ov090_022990e0();
    } else {
        unsigned short v = data_021fbe40.field;
        if ((v & 2) != 0) {
            ret = 7;
        } else if ((v & 0x800) != 0) {
            ret = 0;
        } else if ((v & 0x400) != 0) {
            ret = 5;
        } else if ((v & 4) != 0) {
            ret = 4;
        }
    }

    return func_ov115_0229e4cc(p, ret);
}

int func_ov115_0229e4cc(void *self, int type)
{
    int result;

    result = func_020ee45c(self);
    if (type == -1 || type == 2) {
        // nothing
    } else {
        func_ov090_022993cc(result, (unsigned char) type);
        *((char *) self + 0x8C) = 2;
        func_ov002_022080a0((void *) (self), 1);
        return 1;
    }
    return 0;
}

void func_ov115_0229e47c(void *p)
{
    int sp0;
    func_ov115_0229e2e0();
    func_ov115_0229e2c8(p);
    func_ov115_0229e2b0(p);
    sp0 = 0x30;
    func_ov002_02207f20(p, 0xb, 0, 0, sp0);
    func_02002708(3);
    func_02002708(6);
    func_ov115_0229dda8(p, 1);
    func_ov115_0229e3a8(p);
    func_ov002_02208090(p, 1);
}

void func_ov115_0229e454(void *r0)
{
    if (func_ov002_02207f48(r0, 0) != 0) {
        func_ov002_022080a0(r0, 2);
        func_ov115_0229df6c((int) r0);
    }
    func_ov115_0229e3a8(r0);
}

void func_ov115_0229e41c(char *p)
{
    func_ov115_0229deb4(p);
    func_ov002_02207f04(p, 0xb, 0, 0, 0x30);
    func_ov115_0229e3a8(p);
    func_ov002_02208090(p, 3);
    p += 0xf8;
    func_ov114_0229c8b4(p);
}

void func_ov115_0229e3e4(int arg)
{
    if (func_ov002_02207f3c(arg, 0) != 0) {
        func_020027f0(3);
        func_020027f0(6);
        func_020027f0(4);
        func_ov002_022080a0((void *) (arg), 5);
    } else {
        func_ov115_0229e3a8((void *) arg);
    }
}

void func_ov115_0229e3a8(void *p)
{
    func_ov002_02207e80(p, 3, 0, 0);
    func_ov002_02207e80(p, 6, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
    ((int *) p)[0x1424 / 4] = func_ov002_02207f60(p);
}

void func_ov115_0229e384(Func225E384Struct *obj)
{
    obj->unk_1428 = 0;
    func_ov114_0229d8d0((char *) obj + 0xf8, 3, 6, 4, 0);
}

void func_ov115_0229e36c(void *p)
{
    func_ov114_0229d8ac((char *) p + 0xf8);
    func_ov115_0229df50(p);
}
