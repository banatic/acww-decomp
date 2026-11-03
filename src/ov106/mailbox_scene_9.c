/* mailbox_scene_9: 19 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229ef2c @ 0x0229ef2c, 0x4 bytes, Thumb
 * func_ov106_0229ef28 @ 0x0229ef28, 0x4 bytes, Thumb
 * func_ov106_0229eed0 @ 0x0229eed0, 0x58 bytes, Thumb
 * func_ov106_0229eeb4 @ 0x0229eeb4, 0x1c bytes, Thumb
 * func_ov106_0229ee44 @ 0x0229ee44, 0x70 bytes, Thumb
 * func_ov106_0229ede4 @ 0x0229ede4, 0x60 bytes, Thumb
 * func_ov106_0229ed98 @ 0x0229ed98, 0x4c bytes, Thumb
 * func_ov106_0229ed38 @ 0x0229ed38, 0x60 bytes, Thumb
 * func_ov106_0229ece8 @ 0x0229ece8, 0x50 bytes, Thumb
 * func_ov106_0229ec8c @ 0x0229ec8c, 0x5c bytes, Thumb
 * func_ov106_0229ec0c @ 0x0229ec0c, 0x80 bytes, Thumb
 * func_ov106_0229ebcc @ 0x0229ebcc, 0x3e bytes, Thumb
 * func_ov106_0229eba0 @ 0x0229eba0, 0x2a bytes, Thumb
 * func_ov106_0229eb48 @ 0x0229eb48, 0x58 bytes, Thumb
 * func_ov106_0229eb28 @ 0x0229eb28, 0x20 bytes, Thumb
 * func_ov106_0229eafc @ 0x0229eafc, 0x2c bytes, Thumb
 * func_ov106_0229eadc @ 0x0229eadc, 0x20 bytes, Thumb
 * func_ov106_0229ea08 @ 0x0229ea08, 0xd4 bytes, Thumb
 * func_ov106_0229e9c0 @ 0x0229e9c0, 0x48 bytes, Thumb
 */

struct UnkStruct_0229eadc {
    char pad_00[0x9c];
    int unk_9C;
};

extern unsigned char *func_020978bc(unsigned char *a, int b);
extern unsigned char *func_020984e8(void);
extern unsigned char *func_020989b4(int object);
extern unsigned char *func_02098090(unsigned char *a, int b);
extern void func_0206fc4c(int a);
extern int func_02066830(unsigned char *a, unsigned char *b);
extern void func_020ee470(unsigned char *a);
extern void func_ov106_0229e8f4(void);
extern void func_ov106_0229e8e0(void *p);
extern void func_ov002_02208090(void *p, int n);
extern void func_ov106_0229e860(char *p);
extern void func_ov094_0229ad20(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b274(int a, int b);
extern void func_ov106_0229d104(void *p);
extern void func_ov002_02207f20(void *a, int b, int c, int d, int e);
extern void func_02002708(int a);
extern void func_ov106_0229c354(void *p, int b);
extern void *func_ov002_02207f48(void *a, int b);
extern void func_ov002_02207e90(void *a, int b);
extern void func_ov106_0229e88c(void *self);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov106_0229c364(void *p, int a);
extern void func_ov106_0229c344(void *p, int a);
extern void func_ov106_0229d73c(void *p);
extern int func_ov002_02207d24(void *, int);
extern void func_ov106_0229cc50(void *);
extern void *func_020ee45c(void *);
extern void func_ov092_02299324(void *, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern int func_ov002_02207f3c(void *param, int flag);
extern void func_020027f0(int size);
extern int func_ov106_0229d20c(unsigned char *a, unsigned char b);
extern void func_ov106_0229d1b8(unsigned char *a, int b);
extern void func_020664a8(int a);
extern void func_0206e230(unsigned char *a, int b, int c, int d, int e);
extern void func_ov002_0220b53c(unsigned char *a, int b);
extern int func_0206fe60(void);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(int);
extern int func_ov002_02207f54(void *p);
extern void func_ov094_0229af40(void *a, int b);
extern void func_ov094_0229bbd8(void *a, int b);
extern void func_ov094_0229a2b0(void *a, int b);
extern void func_ov002_02209e18(void *a);
extern void func_ov002_02209984(void *a, int b, int c, int d);
extern void func_0206e2ec(void *a, int b);
extern void func_02066650(void *a);
extern void func_ov106_0229d3b0(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov002_02209178(void *);
extern void func_0206e2e4(void *);
extern void func_ov002_0220af74(void *);

void func_ov106_0229ec8c(void *self);
void func_ov106_0229ec0c(unsigned char *p);
void func_ov106_0229eb28(void *p);
void func_ov106_0229eafc(int arg0);
void func_ov106_0229eadc(struct UnkStruct_0229eadc *self);

int func_ov106_0229ef2c(void)
{
    return 1;
}

int func_ov106_0229ef28(void)
{
    return 1;
}

int func_ov106_0229eed0(unsigned char *self)
{
    unsigned char *p;
    int i;

    func_0206fc4c(1);
    p = func_02098090(func_020989b4((int) ((void) (func_020978bc(self + 0x2bb4, 10)), func_020984e8())), 0);
    for (i = 0; i < 10; i++) {
        func_02066830(p, self + 0x2bb4 + i * 256);
        p += 0x100;
    }
    func_020ee470(self);
    return 1;
}

void func_ov106_0229eeb4(void *p)
{
    func_ov106_0229e8f4();
    func_ov106_0229e8e0(p);
    func_ov002_02208090(p, 1);
}

void func_ov106_0229ee44(char *self)
{
    func_ov106_0229e860(self);
    func_ov094_0229ad20(self + 0xf8);
    func_ov094_0229b2b0(self + 0x0b58);
    func_ov094_0229b274((int) (self + 0x0b58), (int) (self + 0x2bb4));
    func_ov106_0229d104(self);
    func_ov002_02207f20(self, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(self, 2);
    func_ov106_0229c354(self, 1);
    func_ov106_0229c354(self, 2);
    func_ov106_0229eafc((int) self);
}

void func_ov106_0229ede4(void *param)
{
    void *res;
    res = func_ov002_02207f48(param, 0);
    func_ov106_0229eafc((int) param);
    if (res != 0) {
        func_ov106_0229e88c(param);
        func_ov002_02207f20(param, 2, 0, 2, 0x30);
        func_ov002_02207e90(param, 0xC0);
        func_02002708(4);
        func_ov106_0229c354(param, 0x200);
        func_ov106_0229eadc((struct UnkStruct_0229eadc *) param);
        func_ov002_02208090(param, 3);
    }
}

void func_ov106_0229ed98(void *p)
{
    if ((int) func_ov002_02207f48(p, 0) != 0) {
        func_ov002_022080a0((void *) (p), 2);
        if (func_ov106_0229c364(p, 0x4000) != 0) {
            func_ov106_0229c344(p, 0x4000);
            func_ov002_02208098((void *) (p), 0x24);
        } else {
            func_ov106_0229d73c(p);
        }
    }
    func_ov106_0229eadc((struct UnkStruct_0229eadc *) p);
}

void func_ov106_0229ed38(void *self)
{
    func_ov002_02207d24((char *) self + 0x21b8, 1);
    func_ov106_0229cc50(self);
    if (func_ov106_0229c364(self, 0x100) == 0) {
        func_ov092_02299324(func_020ee45c(self), 0x44, 1);
    }
    func_ov002_02207f04(self, 2, 0, 2, 0x30);
    func_ov002_02207e90(self, 0xc0);
    func_ov002_02208090(self, 5);
}

void func_ov106_0229ece8(void *arg)
{
    if (func_ov002_02207f3c(arg, 0)) {
        func_020027f0(4);
        func_ov106_0229c344(arg, 0x200);
        func_ov002_02207f04(arg, 8, 0, 0, 0x30);
        func_ov002_02208090(arg, 6);
        func_ov106_0229ec8c(arg);
    } else {
        func_ov106_0229eadc((struct UnkStruct_0229eadc *) arg);
    }
}

void func_ov106_0229ec8c(void *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(6);
        func_ov106_0229c344(self, 2);
        if (func_ov106_0229c364(self, 0x100) != 0) {
            func_ov002_02208090(self, 7);
            func_ov106_0229ec0c((unsigned char *) self);
        } else {
            func_ov106_0229c344(self, 1);
            func_ov002_022080a0((void *) (self), 5);
        }
    } else {
        func_ov106_0229eafc((int) self);
    }
}

void func_ov106_0229ec0c(unsigned char *p)
{
    int t;

    t = func_ov106_0229d20c(p, p[0xb9]);
    func_ov106_0229d1b8(p, t);
    func_020664a8(t);
    func_0206e230(p + 0x2814, t, 3, 4, 1);
    func_ov002_02207f20((void *) p, 3, 0, 0, 0x30);
    func_02002708(3);
    func_02002708(4);
    func_ov106_0229eb28((void *) p);
    func_ov002_02208090((void *) p, 8);
    func_ov002_0220b53c(p + 0x2b3c, 0x88);
    func_ov106_0229c354((void *) p, 0x80);
}

void func_ov106_0229ebcc(int arg0)
{
    if ((int) func_ov002_02207f48((void *) arg0, 0) != 0) {
        if (((void) ((int) func_ov002_022080a0((void *) (arg0), 2)), func_0206fe60()) != 0) {
            func_ov002_02208098((void *) (arg0), 5);
        } else {
            func_ov002_02208098((void *) (arg0), 9);
        }
    } else {
        func_ov106_0229eb28((void *) arg0);
    }
}

void func_ov106_0229eba0(void *param)
{
    func_ov002_02207f04(param, 3, 0, 0, 0x30);
    func_ov106_0229eb28(param);
    func_ov002_02208090(param, 0xa);
}

void func_ov106_0229eb48(void *self)
{
    if (func_ov002_02207f3c(self, 0) != 0) {
        func_020027f0(3);
        func_020027f0(4);
        func_ov106_0229c344(self, 0x80);
        if (func_ov106_0229c364(self, 0x8000) != 0) {
            func_ov002_022080a0((void *) (self), 5);
            func_ov106_0229c344(self, 1);
        } else {
            func_ov106_0229eeb4(self);
        }
    } else {
        func_ov106_0229eb28(self);
    }
}

void func_ov106_0229eb28(void *p)
{
    func_ov002_02207e80(p, 3, 0, 0);
    func_ov002_02207e80(p, 4, 0, 0);
}

void func_ov106_0229eafc(int arg0)
{
    int local_0;
    int local_4;

    func_ov002_02207e80((void *) arg0, 6, 0, ~0xf);
    local_0 = func_ov002_02207f60(arg0);
    *(int *) (arg0 + 0x98) = local_0;
    local_4 = func_ov002_02207f60(arg0);
    *(int *) (arg0 + 0xa0) = local_4;
}

void func_ov106_0229eadc(struct UnkStruct_0229eadc *self)
{
    func_ov002_02207e80(self, 4, 0, ~0xf);
    self->unk_9C = func_ov002_02207f54(self);
}

void func_ov106_0229ea08(unsigned char *self)
{
    int i;
    unsigned char *p;

    *(int *) (self + 0x94) = 0;
    func_ov094_0229af40(self + 0xf8, 2);
    func_ov094_0229bbd8(self + 0xb58, 1);
    func_ov094_0229a2b0(self + 0xb80, 6);
    self[0xb6] = 0x20;
    func_ov002_02209e18(self + 0x2288);
    self[0xb4] = 0;
    self[0xb8] = 0xb;
    func_ov002_02209984(self + 0x2304, 3, 0, 0);
    func_0206e2ec(self + 0x2814, 3);
    for (i = 0; i < 10; i++) {
        func_02066650(self + 0x2bb4 + i * 0x100);
    }
    p = func_02098090(func_020989b4((int) func_020984e8()), 0);
    for (i = 0; i < 10; i++) {
        func_02066830((unsigned char *) (self + 0x2bb4 + i * 0x100), p);
        p += 0x100;
    }
    func_ov106_0229c354(self, 0x4000);
    self[0xbf] = 0;
}

void func_ov106_0229e9c0(void *self)
{
    func_ov106_0229d3b0(self);
    func_ov094_0229a038((char *) self + 0xb80);
    func_ov094_0229af18((char *) self + 0xf8);
    func_ov002_02209178((char *) self + 0x2304);
    func_0206e2e4((char *) self + 0x2814);
    func_ov002_0220af74((char *) self + 0x3fb4);
}
