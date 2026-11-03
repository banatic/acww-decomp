/* pockets_swap_6: 11 functions, module ov107
 * mwccarm 1.2/base -O4,s
 * func_ov107_0229de88 @ 0x0229de88, 0x1c bytes, Thumb
 * func_ov107_0229de84 @ 0x0229de84, 0x4 bytes, Thumb
 * func_ov107_0229de80 @ 0x0229de80, 0x4 bytes, Thumb
 * func_ov107_0229de70 @ 0x0229de70, 0x10 bytes, Thumb
 * func_ov107_0229de54 @ 0x0229de54, 0x1c bytes, Thumb
 * func_ov107_0229ddc4 @ 0x0229ddc4, 0x90 bytes, Thumb
 * func_ov107_0229dd88 @ 0x0229dd88, 0x3a bytes, Thumb
 * func_ov107_0229dd28 @ 0x0229dd28, 0x60 bytes, Thumb
 * func_ov107_0229dcdc @ 0x0229dcdc, 0x4c bytes, Thumb
 * func_ov107_0229dc58 @ 0x0229dc58, 0x84 bytes, Thumb
 * func_ov107_0229dc18 @ 0x0229dc18, 0x40 bytes, Thumb
 */

struct UnkStruct_0229ddc4 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x10c - 0x9c];
    char unk_10C;
    char pad_10D[0xb6c - 0x10d];
    char unk_B6C;
    char pad_B6D[0x2828 - 0xb6d];
    char unk_2828;
};

typedef struct {
    unsigned char data[0x2318];
} UnkStruct_0229dc58;

extern void func_ov107_0229dbfc(void *);
extern void func_ov107_0229dea4(void *);
extern void func_ov107_0229dbf4(void *);
extern void func_020ee470(void *argument0);
extern void func_ov107_0229db5c(void);
extern void func_ov107_0229db48(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov107_0229db24(void *p);
extern int func_ov002_0220ab84(void *p, int x);
extern void func_ov094_0229ad20(void *p);
extern void func_ov107_0229d224(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b794(void *p, int x);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int x);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov107_0229c2a4(void *p, int x);
extern int func_ov002_02207f60(void *p);
extern int func_ov002_02207f48(void *a, int b);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov107_0229d480(void *a);
extern int func_ov002_02207d24(void *p, int v);
extern void func_ov107_0229ce90(void *p);
extern void *func_020ee45c(void *p);
extern void func_ov092_02299324(void *p, int a, int b);
extern void func_ov002_02207f04(void *p, int a, int b, int c, int d);
extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern void func_ov107_0229c294(void *, int);
extern void func_ov094_0229af40(unsigned char *, int);
extern void func_ov094_0229bbd8(unsigned char *, int);
extern void func_ov094_0229a2b0(unsigned char *, int);
extern void func_ov002_02209e18(unsigned char *);
extern void func_ov002_02209984(unsigned char *, int, int, int _x);
extern int func_ov107_0229c5b0(UnkStruct_0229dc58 *);
extern void func_ov107_0229d394(void *);
extern void func_ov094_0229a038(void *);
extern void func_ov094_0229af18(void *);
extern void func_ov002_02209178(void *);
extern void func_ov002_0220af74(void *);

int func_ov107_0229de88(void *p)
{
    func_ov107_0229dbfc(p);
    func_ov107_0229dea4(p);
    func_ov107_0229dbf4(p);
    return 1;
}

int func_ov107_0229de84(void)
{
    return 1;
}

int func_ov107_0229de80(void)
{
    return 1;
}

int func_ov107_0229de70(void *argument0)
{
    func_020ee470(argument0);
    return 1;
}

void func_ov107_0229de54(void *arg)
{
    func_ov107_0229db5c();
    func_ov107_0229db48(arg);
    func_ov002_02208090(arg, 1);
}

void func_ov107_0229ddc4(struct UnkStruct_0229ddc4 *p)
{
    func_ov107_0229db24(p);
    func_ov002_0220ab84(&p->unk_2828, 0x65);
    func_ov094_0229ad20(&p->unk_10C);
    func_ov107_0229d224(p);
    func_ov094_0229b2b0(&p->unk_B6C);
    func_ov094_0229b794(&p->unk_B6C, 0xf);
    func_ov002_02207f20(p, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(p, 6, 0, -16);
    func_ov002_02208090(p, 2);
    func_ov107_0229c2a4(p, 1);
    func_ov107_0229c2a4(p, 2);
    p->unk_98 = func_ov002_02207f60(p);
}

void func_ov107_0229dd88(void *a)
{
    if (func_ov002_02207f48(a, 0) != 0) {
        func_ov002_022080a0((void *) (a), 2);
        func_ov107_0229d480(a);
    }
    func_ov002_02207e80(a, 6, 0, ~0xF);
    *(unsigned int *) ((char *) a + 0x98) = func_ov002_02207f60(a);
}

void func_ov107_0229dd28(char *p)
{
    func_ov002_02207d24(p + 0x21cc, 1);
    func_ov107_0229ce90(p);
    func_ov092_02299324(func_020ee45c(p), 0x44, 1);
    func_ov002_02207f04(p, 8, 0, 0, 0x30);
    func_ov002_02207e80(p, 6, 0, ~0xf);
    func_ov002_02208090(p, 4);
    *(int *) (p + 0x98) = func_ov002_02207f60(p);
}

void func_ov107_0229dcdc(void *param)
{
    if (func_ov002_02207f3c(param, 0) != 0) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (param), 5);
        func_ov107_0229c294(param, 1);
        func_ov107_0229c294(param, 2);
    } else {
        func_ov002_02207e80(param, 6, 0, -16);
    }
    *(int *) ((char *) param + 0x98) = func_ov002_02207f60(param);
}

void func_ov107_0229dc58(UnkStruct_0229dc58 *self)
{
    *(int *) (self->data + 0x94) = 0;
    func_ov094_0229af40(self->data + 0x10c, 2);
    func_ov094_0229bbd8(self->data + 0xb6c, 2);
    func_ov094_0229a2b0(self->data + 0xb94, 6);
    self->data[0xb7] = 16;
    func_ov002_02209e18(self->data + 0x229c);
    self->data[0xb5] = 0;
    self->data[0xb8] = 0;
    func_ov002_02209984(self->data + 0x2318, 3, 1, 0);
    if (func_ov107_0229c5b0(self) != 0) {
        func_ov107_0229c2a4((void *) self, 0x40);
    }
    self->data[0xbf] = 0;
}

void func_ov107_0229dc18(void *self)
{
    func_ov107_0229d394(self);
    func_ov094_0229a038((char *) self + 0xb94);
    func_ov094_0229af18((char *) self + 0x10c);
    func_ov002_02209178((char *) self + 0x2318);
    func_ov002_0220af74((char *) self + 0x2828);
}
