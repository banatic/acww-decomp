/* star_view_2: 17 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229c5f8 @ 0x0229c5f8, 0x4 bytes, Thumb
 * func_ov128_0229c5f4 @ 0x0229c5f4, 0x4 bytes, Thumb
 * func_ov128_0229c5e4 @ 0x0229c5e4, 0x10 bytes, Thumb
 * func_ov128_0229c58c @ 0x0229c58c, 0x58 bytes, Thumb
 * func_ov128_0229c554 @ 0x0229c554, 0x38 bytes, Thumb
 * func_ov128_0229c50c @ 0x0229c50c, 0x46 bytes, Thumb
 * func_ov128_0229c4d0 @ 0x0229c4d0, 0x3c bytes, Thumb
 * func_ov128_0229c4ac @ 0x0229c4ac, 0x24 bytes, Thumb
 * func_ov128_0229c464 @ 0x0229c464, 0x46 bytes, Thumb
 * func_ov128_0229c408 @ 0x0229c408, 0x5c bytes, Thumb
 * func_ov128_0229c398 @ 0x0229c398, 0x70 bytes, Thumb
 * func_ov128_0229c390 @ 0x0229c390, 0x8 bytes, Thumb
 * func_ov128_0229c37c @ 0x0229c37c, 0x14 bytes, Thumb
 * func_ov128_0229c350 @ 0x0229c350, 0x2c bytes, Thumb
 * func_ov128_0229c334 @ 0x0229c334, 0x1c bytes, Thumb
 * func_ov128_0229c2fc @ 0x0229c2fc, 0x38 bytes, Thumb
 * func_ov128_0229c2a0 @ 0x0229c2a0, 0x5c bytes, Thumb
 */

typedef struct {
    char pad_00[0x2d50];
    int unk_2D50;
} UnkStruct_0229c4ac;

extern void func_020ee470(void *argument0);
extern void func_ov002_02207f20(void *self, int, int, int, int);
extern void func_02002708(int);
extern void func_ov128_0229b7dc(void *self, int);
extern void func_02001d60(int, int);
extern void func_ov002_02208090(void *self, int);
extern int func_ov002_02207f48(void *a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov128_0229be00(void *a);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(void *x, int y);
extern void func_020027f0(int x);
extern void func_02001b6c(int x);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);
extern void func_02001b7c(int);
extern void func_02002808(int, int, int, int, int);
extern void func_ov127_0229a0bc(void *p);
extern void func_ov128_0229baa8(void *p);
extern int func_ov004_0222be7c(void);
extern void func_0203584c(void *p);
extern unsigned char data_021c526c[];
extern void func_020b1774(void *);
extern void func_ov127_02299e5c(void *);
extern void func_ov002_0220b290(void *);
extern void func_02070b84(void *);
extern int func_02095904(void);
extern void func_02035834(void *);
extern int func_02002c6c(void *, void *, int, int, int, int);
extern void *data_021fbe94;
extern char data_ov128_0229cd20;
extern void func_ov128_0229b88c(void *p);
extern void func_020b1800(void *);
extern void func_ov127_02299e64(void *);
extern void func_ov128_0229b804(void *);
extern void func_02001c08(int);
extern void func_020029e8(int, int);
extern void func_020028bc(int, int, int, int);
extern void func_ov127_0229a04c(void *self, int a);
extern void func_ov127_02299fd4(unsigned char *self, unsigned char val, int mode);
extern void func_020b177c(void *self, int a);
extern void func_ov127_02299f90(void *receiver);
extern void func_ov002_0220b36c(void *self, const void *data, int a, int b);
extern void func_ov002_0220b338(char *self, int value);
extern void func_ov128_0229bb20(void *self);
extern const unsigned char data_ov128_0229cb38[];

void func_ov128_0229c4ac(UnkStruct_0229c4ac *self);
void func_ov128_0229c464(int param);
void func_ov128_0229c350(void *self);
void func_ov128_0229c334(void *param);
void func_ov128_0229c2fc(void);
void func_ov128_0229c2a0(void *self);

int func_ov128_0229c5f8(void)
{
    return 1;
}

int func_ov128_0229c5f4(void)
{
    return 1;
}

int func_ov128_0229c5e4(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov128_0229c58c(void *self)
{
    func_ov128_0229c2fc();
    func_ov128_0229c2a0(self);
    func_ov002_02207f20(self, 9, 4, 0, 0x30);
    func_02002708(3);
    func_02002708(6);
    func_ov128_0229b7dc(self, 1);
    func_02001d60(0x1e, 1);
    func_ov128_0229c464((int) self);
    func_ov128_0229c4ac((UnkStruct_0229c4ac *) self);
    func_ov002_02208090(self, 1);
}

void func_ov128_0229c554(void *arg)
{
    if (func_ov002_02207f48(arg, 0)) {
        func_ov002_022080a0((void *) (arg), 2);
        func_ov128_0229be00(arg);
        func_ov128_0229b7dc(arg, 4);
    } else {
        func_ov128_0229c464((int) arg);
    }
    func_ov128_0229c4ac((UnkStruct_0229c4ac *) arg);
}

void func_ov128_0229c50c(void *arg)
{
    func_ov092_02299324(func_020ee45c(arg), 0x44, 1);
    func_ov002_02207f04(arg, 9, 0, 0, 48);
    func_02001d60(30, 1);
    func_ov128_0229c464((int) arg);
    func_ov128_0229c4ac((UnkStruct_0229c4ac *) arg);
    func_ov002_02208090(arg, 3);
}

void func_ov128_0229c4d0(void *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(3);
        func_020027f0(6);
        func_02001b6c(2);
        func_ov002_022080a0((void *) (param), 5);
    } else {
        func_ov128_0229c464((int) param);
        func_ov128_0229c4ac((UnkStruct_0229c4ac *) param);
    }
}

void func_ov128_0229c4ac(UnkStruct_0229c4ac *self)
{
    func_ov002_02207e80(self, 6, 0, 0);
    self->unk_2D50 = func_ov002_02207f60(self);
}

void func_ov128_0229c464(int param)
{
    int u;
    int v;

    u = func_ov002_02207f60((void *) param) - 64;
    if (u < 0) {
        u = 0;
    }

    v = func_ov002_02207f60((void *) param) - 48;

    if (v > 0) {
        goto then;
    }
    func_02001b6c(2);
    goto end;
then:
    func_02001b7c(2);
    func_02002808(3, 0, u, 0xff, v);
end:;
}

void func_ov128_0229c408(void *self)
{
    unsigned short *p16;
    unsigned int *p32;
    unsigned char *p8;
    void *p;

    p16 = (unsigned short *) ((char *) self + 0x2d68);
    *p16 = 0;
    p = (char *) self + 0x4a4;
    func_ov127_0229a0bc(p);
    p32 = (unsigned int *) ((char *) self + 0x2d48);
    *p32 = 0x80;
    p32 = (unsigned int *) ((char *) self + 0x2d4c);
    *p32 = 0x60;
    p8 = (unsigned char *) ((char *) self + 0x2d6c);
    *p8 = 1;
    func_ov128_0229baa8(self);
    func_ov004_0222be7c();
    p = *(void **) data_021c526c;
    p = (char *) p + 0x2f0;
    func_0203584c(p);
}

void func_ov128_0229c398(char *obj)
{
    func_020b1774(obj + 0x174);
    func_ov127_02299e5c(obj + 0x4a4);
    func_ov002_0220b290(obj + 0x94);
    func_02070b84(obj + 0x2cdc);
    func_02095904();
    func_02035834((char *) (*(void * *) data_021c526c) + 0x2f0);
    func_02002c6c(&data_ov128_0229cd20, data_021fbe94, 3, 0, 0x10, 0x10);
}

void func_ov128_0229c390(void *argument0)
{
    func_ov128_0229c350(argument0);
}

void func_ov128_0229c37c(void *p)
{
    func_ov128_0229b88c(p);
    func_ov128_0229c334(p);
}

void func_ov128_0229c350(void *self)
{
    func_02070b84((char *) self + 0x2cdc);
    func_020b1800((char *) self + 0x174);
    func_ov002_0220b290((char *) self + 0x94);
}

void func_ov128_0229c334(void *param)
{
    func_ov127_02299e64((char *) param + 0x4a4);
    func_ov128_0229b804(param);
}

void func_ov128_0229c2fc(void)
{
    func_02001c08(0);
    func_020029e8(3, 2);
    func_020028bc(3, 1, 0, 0);
    func_020029e8(6, 1);
    func_020028bc(6, 0, 0, 0);
}

void func_ov128_0229c2a0(void *self)
{
    func_ov127_0229a04c((char *) self + 0x4a4, 3);
    func_ov127_02299fd4((unsigned char *) self + 0x4a4, 6, 0);
    func_020b177c((char *) self + 0x174, 3);
    func_ov127_02299f90((void *) ((char *) self + 0x4a4));
    func_ov002_0220b36c((char *) self + 0x94, data_ov128_0229cb38, 6, 2);
    func_ov002_0220b338((char *) self + 0x94, 0x69);
    func_ov128_0229bb20(self);
}
