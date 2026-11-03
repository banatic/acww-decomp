/* pockets_pick_6: 10 functions, module ov101
 * mwccarm 1.2/base -O4,s
 * func_ov101_0229db90 @ 0x0229db90, 0x4 bytes, Thumb
 * func_ov101_0229db8c @ 0x0229db8c, 0x4 bytes, Thumb
 * func_ov101_0229db7c @ 0x0229db7c, 0x10 bytes, Thumb
 * func_ov101_0229db60 @ 0x0229db60, 0x1c bytes, Thumb
 * func_ov101_0229dad4 @ 0x0229dad4, 0x8c bytes, Thumb
 * func_ov101_0229da98 @ 0x0229da98, 0x3a bytes, Thumb
 * func_ov101_0229da38 @ 0x0229da38, 0x60 bytes, Thumb
 * func_ov101_0229d9ec @ 0x0229d9ec, 0x4c bytes, Thumb
 * func_ov101_0229d97c @ 0x0229d97c, 0x70 bytes, Thumb
 * func_ov101_0229d940 @ 0x0229d940, 0x3c bytes, Thumb
 */

typedef struct UnkStruct_0229dad4 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x58];
    int unk_F4;
    char pad_F8[0xa5c];
    int unk_B54;
    char pad_B58[0x1cb8];
    int unk_2810;
} UnkStruct_0229dad4;

struct UnkStruct_0229da38 {
    char pad_00[0x98];
    int unk_98;
};

extern void func_020ee470(void *parameter0);
extern void func_ov101_0229d888(void);
extern void func_ov101_0229d874(void *object);
extern void func_ov101_0229d850(void *);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov094_0229ad20(void *);
extern void func_ov101_0229cc80(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov094_0229b794(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov101_0229c29c(void *, int);
extern int func_ov002_02207f60(void *);
extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern void func_ov101_0229cf80(void *p);
extern int func_ov002_02207d24(void *addr, int n);
extern void func_ov101_0229c844(void *self);
extern int func_020ee45c(void *self);
extern void func_ov092_02299324(int v, int a, int b);
extern void func_ov002_02207f04(void *self, int a, int b, int c, int d);
extern int func_ov002_02207f3c(char *p, int a);
extern void func_020027f0(int a);
extern void func_ov101_0229c28c(char *p, int a);
extern void func_ov094_0229af40(unsigned char *p, int n);
extern void func_ov094_0229bbd8(unsigned char *p, int n);
extern void func_ov094_0229a2b0(unsigned char *p, int n);
extern void func_ov002_02209e18(unsigned char *p);
extern void func_ov002_02209984(unsigned char *p, int a, int b, int _x);
extern void func_ov101_0229ce44(char *p);
extern void func_ov094_0229a038(char *p);
extern void func_ov094_0229af18(char *p);
extern void func_ov002_02209178(char *p);
extern void func_ov002_0220af74(char *p);

int func_ov101_0229db90(void)
{
    return 1;
}

int func_ov101_0229db8c(void)
{
    return 1;
}

int func_ov101_0229db7c(void *arg0)
{
    func_020ee470((void *) arg0);
    return 1;
}

void func_ov101_0229db60(void *param)
{
    func_ov101_0229d888();
    func_ov101_0229d874(param);
    func_ov002_02208090(param, (unsigned char) 1);
}

void func_ov101_0229dad4(UnkStruct_0229dad4 *obj)
{
    int zero = 0;
    func_ov101_0229d850(obj);
    func_ov002_0220ab84(&obj->unk_2810, 0x65);
    func_ov094_0229ad20(&obj->unk_F4);
    func_ov101_0229cc80(obj);
    func_ov094_0229b2b0(&obj->unk_B54);
    func_ov094_0229b794(&obj->unk_B54, 0xf);
    func_ov002_02207f20(obj, 8, zero, zero, 0x30);
    func_02002708(6);
    func_ov002_02207e80(obj, 6, 0, -16);
    func_ov002_02208090(obj, 2);
    func_ov101_0229c29c(obj, 1);
    func_ov101_0229c29c(obj, 2);
    obj->unk_98 = func_ov002_02207f60(obj);
}

void func_ov101_0229da98(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0(p, 2);
        func_ov101_0229cf80(p);
    }
    func_ov002_02207e80(p, 6, 0, ~0xf);
    *(int *) ((char *) p + 0x98) = func_ov002_02207f60(p);
}

void func_ov101_0229da38(struct UnkStruct_0229da38 *self)
{
    int r;

    func_ov002_02207d24((char *) self + 0x21b4, 1);
    func_ov101_0229c844(self);
    r = func_020ee45c(self);
    func_ov092_02299324(r, 0x44, 1);
    func_ov002_02207f04(self, 8, 0, 0, 0x30);
    func_ov002_02207e80(self, 6, 0, (int) 0xfffffff0);
    func_ov002_02208090(self, 4);
    self->unk_98 = func_ov002_02207f60(self);
}

void func_ov101_0229d9ec(char *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((void *) p, 5);
        func_ov101_0229c28c(p, 1);
        func_ov101_0229c28c(p, 2);
    } else {
        func_ov002_02207e80((void *) p, 6, 0, -16);
    }
    *(int *) (p + 0x98) = func_ov002_02207f60((void *) p);
}

void func_ov101_0229d97c(unsigned char *self)
{
    *(unsigned int *) (self + 0x94) = 0;
    func_ov094_0229af40(self + 0xf4, 2);
    func_ov094_0229bbd8(self + 0xb54, 2);
    func_ov094_0229a2b0(self + 0xb7c, 6);
    *(unsigned char *) (self + 0xb1) = 0x10;
    func_ov002_02209e18(self + 0x2284);
    *(unsigned char *) (self + 0xaf) = 0;
    *(unsigned char *) (self + 0xb3) = 0;
    func_ov002_02209984(self + 0x2300, 3, 1, 0);
    *(unsigned char *) (self + 0xb9) = 0;
}

void func_ov101_0229d940(char *obj)
{
    func_ov101_0229ce44(obj);
    func_ov094_0229a038(obj + 0xB7C);
    func_ov094_0229af18(obj + 0xF4);
    func_ov002_02209178(obj + 0x2300);
    func_ov002_0220af74(obj + 0x2810);
}
