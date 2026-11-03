/* public_box_5: 7 functions, module ov110
 * mwccarm 1.2/base -O4,s
 * func_ov110_0229d894 @ 0x0229d894, 0x1c bytes, Thumb
 * func_ov110_0229d860 @ 0x0229d860, 0x34 bytes, Thumb
 * func_ov110_0229d840 @ 0x0229d840, 0x20 bytes, Thumb
 * func_ov110_0229d7b8 @ 0x0229d7b8, 0x88 bytes, Thumb
 * func_ov110_0229d770 @ 0x0229d770, 0x48 bytes, Thumb
 * func_ov110_0229d728 @ 0x0229d728, 0x48 bytes, Thumb
 * func_ov110_0229d6c4 @ 0x0229d6c4, 0x64 bytes, Thumb
 */

typedef struct {
    char pad_00[0xf3];
    unsigned char unk_F3;
    char pad_F4;
    unsigned char unk_F5;
} UnkStruct_0229d860;

typedef struct Context {
    char pad_00[0xa0];
    int unk_A0;
    int unk_A4;
    char pad_A8[0xf2 - 0xa8];
    unsigned char unk_F2;
    unsigned char unk_F3;
} Context;

extern void func_ov110_0229cbe0(void *);
extern void func_ov110_0229d054(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov110_0229cc58(UnkStruct_0229d860 *self);
extern void func_ov002_02207fc0(UnkStruct_0229d860 *self);
extern void func_ov110_0229ce44(UnkStruct_0229d860 *self);
extern void func_ov110_0229cff8(UnkStruct_0229d860 *self, unsigned char arg);
extern int func_0206fe60(void);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern void func_ov002_02207cf8(void *p);
extern void func_ov094_022999cc(void);
extern int func_ov110_0229d3d8(void *p, int b);
extern int func_ov110_0229d388(void *p, int b);
extern int func_ov110_0229d13c(void *p, int arg);
extern void func_ov110_0229c2a8(void *p, int arg);
extern void func_ov110_0229c2b8(void *p, int arg);
extern int func_ov002_02207d24(unsigned char *ptr, int flag);
extern void func_ov110_0229cd14(unsigned char *self, int val);
extern void func_ov110_0229cde0(unsigned char *self);
extern void func_ov094_022999c0(void);
extern void func_ov110_0229cdb4(void *);
extern void func_ov002_02209d68(void *p, int a, int b);
extern int func_ov002_02209d38(void *p, int a, int b, int c);
extern int func_ov002_02209d8c(void *p);
extern void func_ov110_0229cd8c(void *p);

void func_ov110_0229d894(void *p)
{
    func_ov110_0229cbe0(p);
    func_ov110_0229d054(p);
    func_ov002_02208098((void *) (p), 0);
}

void func_ov110_0229d860(UnkStruct_0229d860 *self)
{
    self->unk_F3 = 0x1f;
    func_ov110_0229cc58(self);
    func_ov002_02207fc0(self);
    func_ov110_0229ce44(self);
    func_ov002_02208098((void *) (self), 4);
    func_ov110_0229cff8(self, self->unk_F5);
}

void func_ov110_0229d840(void *param)
{
    if (func_0206fe60()) {
        func_ov110_0229d894(param);
    } else {
        func_ov110_0229d860((UnkStruct_0229d860 *) param);
    }
}

void func_ov110_0229d7b8(Context *p, int arg1)
{
    unsigned char g1, g2;

    p->unk_F2 = (unsigned char) arg1;
    func_ov002_02208098((void *) (p), 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    p->unk_A0 = func_ov110_0229d3d8(p, p->unk_F2) - g1;
    p->unk_A4 = func_ov110_0229d388(p, p->unk_F2) - g2;
    p->unk_F3 = (unsigned char) arg1;
    func_ov002_02207cf8((char *) p + 0x21f8);
    if (func_ov110_0229d13c(p, arg1) != 0) {
        func_ov110_0229c2a8(p, 4);
    } else {
        func_ov110_0229c2b8(p, 4);
        func_ov094_022999cc();
    }
}

void func_ov110_0229d770(unsigned char *self, int val)
{
    self[0xf4] = (unsigned char) val;
    func_ov002_02207d24(self + 0x21f8, 1);
    func_ov110_0229cd14(self, val);
    if (self[0xf1] == 1) {
        func_ov002_02208098((void *) (self), 3);
    }
    func_ov110_0229cde0(self);
    func_ov094_022999c0();
}

void func_ov110_0229d728(void *p, char val)
{
    unsigned char *base = (unsigned char *) p;
    base[0xf4] = val;
    func_ov002_02207d24((unsigned char *) (base + 0x21f8), 1);
    func_ov110_0229cd14((unsigned char *) p, val);
    if (base[0xf1] == 1) {
        base[0xf8] = 5;
    }
    func_ov110_0229cdb4(p);
    func_ov094_022999c0();
}

unsigned char *func_ov110_0229d6c4(unsigned char *param0, unsigned char param1, int param2)
{
    *(unsigned char *) (param0 + 0xf4) = param1;
    func_ov002_02209d68(param0 + 0x22c8, *(int *) (param0 + 0xa8), *(int *) (param0 + 0xac));
    {
        int ret1 = func_ov110_0229d3d8(param0, (unsigned char) param1);
        int ret2 = func_ov110_0229d388(param0, (unsigned char) param1);
        func_ov002_02209d38(param0 + 0x22c8, ret1, ret2, param2);
    }
    func_ov002_02209d8c(param0 + 0x22c8);
    func_ov110_0229cd8c(param0);
    return func_ov002_02208098((void *) (param0), 0x10);
}
