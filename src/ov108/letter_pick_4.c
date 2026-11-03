/* letter_pick_4: 11 functions, module ov108
 * mwccarm 1.2/base -O4,s
 * func_ov108_0229db80 @ 0x0229db80, 0x1c bytes, Thumb
 * func_ov108_0229db7c @ 0x0229db7c, 0x4 bytes, Thumb
 * func_ov108_0229db78 @ 0x0229db78, 0x4 bytes, Thumb
 * func_ov108_0229db68 @ 0x0229db68, 0x10 bytes, Thumb
 * func_ov108_0229db4c @ 0x0229db4c, 0x1c bytes, Thumb
 * func_ov108_0229dac8 @ 0x0229dac8, 0x84 bytes, Thumb
 * func_ov108_0229da8c @ 0x0229da8c, 0x3a bytes, Thumb
 * func_ov108_0229da2c @ 0x0229da2c, 0x60 bytes, Thumb
 * func_ov108_0229d9e0 @ 0x0229d9e0, 0x4c bytes, Thumb
 * func_ov108_0229d960 @ 0x0229d960, 0x80 bytes, Thumb
 * func_ov108_0229d920 @ 0x0229d920, 0x40 bytes, Thumb
 */

typedef struct {
    char pad_00[0x98];
    int unk_98;
} Func_ov108Struct;

typedef struct {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x2314];
    int unk_23B0;
} UnkStruct_0229da2c;

typedef struct UnkStruct_0229d9e0 {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229d9e0;

extern int func_ov108_0229d904(void *p);
extern void func_ov108_0229db9c(void *p);
extern void func_ov108_0229d8fc(void *p);
extern void func_020ee470(void *argument0);
extern void func_ov108_0229d864(void);
extern void func_ov108_0229d850(int a);
extern void func_ov108_0229d82c(void *);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov094_0229ad20(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov108_0229cbbc(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov108_0229c2cc(void *, int);
extern int func_ov002_02207f60(void *);
extern int func_ov002_02207f48(Func_ov108Struct *obj, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov108_0229cf4c(Func_ov108Struct *obj);
extern int func_ov002_02207d24(void *, int);
extern void func_ov108_0229c794(void *);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(UnkStruct_0229d9e0 *p, int arg);
extern void func_020027f0(int arg);
extern void func_ov108_0229c2bc(UnkStruct_0229d9e0 *p, int arg);
extern void func_ov094_0229af40(void *p, int a);
extern void func_ov094_0229bbd8(void *p, int a);
extern void func_ov094_0229a2b0(void *p, int a);
extern void func_ov002_02209e18(void *p);
extern void func_ov002_02209984(void *p, int a, int b, int _x);
extern void func_ov108_0229cd80(void *p);
extern void func_ov094_0229a038(void *p);
extern void func_ov094_0229af18(void *p);
extern void func_ov002_02209178(void *p);
extern void func_ov002_0220af74(void *p);

int func_ov108_0229db80(void *p)
{
    func_ov108_0229d904(p);
    func_ov108_0229db9c(p);
    func_ov108_0229d8fc(p);
    return 1;
}

int func_ov108_0229db7c(void)
{
    return 1;
}

int func_ov108_0229db78(void)
{
    return 1;
}

int func_ov108_0229db68(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov108_0229db4c(int a)
{
    func_ov108_0229d864();
    func_ov108_0229d850(a);
    func_ov002_02208090((void *) a, 1);
}

void func_ov108_0229dac8(char *self)
{
    func_ov108_0229d82c(self);
    func_ov002_0220ab84(self + 0x2a0c, 0x65);
    func_ov094_0229ad20(self + 0x2f0);
    func_ov094_0229b2b0(self + 0xd50);
    func_ov108_0229cbbc(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(self, 6, 0, ~0xf);
    func_ov002_02208090(self, 2);
    func_ov108_0229c2cc(self, 1);
    func_ov108_0229c2cc(self, 2);
    *(int *) (self + 0x98) = func_ov002_02207f60(self);
}

void func_ov108_0229da8c(Func_ov108Struct *obj)
{
    if (func_ov002_02207f48(obj, 0)) {
        func_ov002_022080a0((void *) (obj), 2);
        func_ov108_0229cf4c(obj);
    }
    func_ov002_02207e80((void *) obj, 6, 0, ~0xf);
    obj->unk_98 = func_ov002_02207f60((void *) obj);
}

void func_ov108_0229da2c(UnkStruct_0229da2c *obj)
{
    func_ov002_02207d24(&obj->unk_23B0, 1);
    func_ov108_0229c794(obj);
    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    func_ov002_02207f04(obj, 8, 0, 0, 0x30);
    func_ov002_02207e80(obj, 6, 0, ~0xf);
    func_ov002_02208090(obj, 4);
    obj->unk_98 = func_ov002_02207f60(obj);
}

void func_ov108_0229d9e0(UnkStruct_0229d9e0 *p)
{
    if (func_ov002_02207f3c(p, 0) != 0) {
        func_020027f0(6);
        func_ov108_0229c2bc(p, 2);
        func_ov108_0229c2bc(p, 1);
        func_ov002_022080a0((void *) (p), 5);
    } else {
        func_ov002_02207e80((void *) p, 6, 0, -16);
    }
    p->unk_98 = func_ov002_02207f60((void *) p);
}

void func_ov108_0229d960(void *self)
{
    char *base = (char *) self;
    int zero = 0;

    *(int *) (base + 0x94) = zero;
    func_ov094_0229af40(base + 0x2f0, 2);
    func_ov094_0229bbd8(base + 0xd50, 2);
    func_ov094_0229a2b0(base + 0xd78, 6);
    base[0x2ae] = 0x16;
    func_ov002_02209e18(base + 0x2480);
    base[0x2ac] = 0;
    base[0x2b0] = 0xb;
    func_ov002_02209984(base + 0x24fc, 3, 1, 0);
    base[0x2b6] = 0;
}

void func_ov108_0229d920(char *p)
{
    func_ov108_0229cd80(p);
    func_ov094_0229a038(p + 0xd78);
    func_ov094_0229af18(p + 0x2f0);
    func_ov002_02209178(p + 0x24fc);
    func_ov002_0220af74(p + 0x2a0c);
}
