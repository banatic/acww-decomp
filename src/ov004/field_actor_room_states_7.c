/* field_actor_room_states_7: 12 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02228318 @ 0x02228318, 0x2c bytes, Thumb
 * func_ov004_02228304 @ 0x02228304, 0x14 bytes, Thumb
 * func_ov004_02228300 @ 0x02228300, 0x4 bytes, Thumb
 * func_ov004_022282c0 @ 0x022282c0, 0x40 bytes, Thumb
 * func_ov004_022282bc @ 0x022282bc, 0x4 bytes, Thumb
 * func_ov004_022282b8 @ 0x022282b8, 0x4 bytes, Thumb
 * func_ov004_022282b0 @ 0x022282b0, 0x6 bytes, Thumb
 * func_ov004_0222820c @ 0x0222820c, 0xa4 bytes, Thumb
 * func_ov004_022281e0 @ 0x022281e0, 0x2c bytes, Thumb
 * func_ov004_0222818c @ 0x0222818c, 0x54 bytes, Thumb
 * func_ov004_02228170 @ 0x02228170, 0x1a bytes, Thumb
 * func_ov004_02228164 @ 0x02228164, 0xc bytes, Thumb
 */

typedef struct {
    unsigned long unk_00;
} UnkStruct_02228300;

typedef struct {
    char pad_00[0xc];
    int data[4];
} UnkStruct_022282c0;

typedef struct {
    unsigned long unk_00;
} UnkStruct_022282bc;

typedef struct {
    unsigned char unk_00;
} UnkStruct_022282b8;

typedef struct UnkStruct_0222818c {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7f0 - 0x2d0 - 4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f0 - 4];
    int unk_7FC;
    int unk_800;
} UnkStruct_0222818c;

typedef struct {
    int unk_00;
    unsigned char unk_04;
    int unk_08;
    int unk_0C;
} Struct0200A4AC;

extern void func_ov004_022283bc(unsigned char *addr, unsigned char *out);
extern int func_ov004_022283cc(unsigned char *addr, unsigned char v, int n, int arg2);
extern void func_02010f5c(void *arg);
extern void func_02010d64(void *arg);
extern unsigned int func_0200e92c(UnkStruct_022282c0 *lp);
extern void func_0200e90c(UnkStruct_022282c0 *lp, int a, int b, int c);
extern int func_0200e894(int p1, UnkStruct_022282c0 *lp);
extern int func_0200e91c(UnkStruct_022282c0 *lp);
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern void func_02056fcc(void *p, unsigned int h, int a, int b, unsigned short g);
extern int func_02073908(int a, int b);
extern int func_ov004_0223b334(void *p, short a);
extern int data_020ccf94;
extern int func_02056f94(int *p);
extern void func_020109fc(void *self, int a, int b, int c);
extern int func_02008258(void *self, int a);

void func_ov004_02228318(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_022283bc(base + 0x8f0, &val);
    func_ov004_022283cc(base, val, 6, arg2);
}

void func_ov004_02228304(void *arg)
{
    func_02010f5c(arg);
    func_02010d64(arg);
}

void func_ov004_02228300(UnkStruct_02228300 *p, unsigned long v)
{
    p->unk_00 = v;
}

int func_ov004_022282c0(int p1, int p2, int p3, int p4)
{
    UnkStruct_022282c0 local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x2f, p3, p4);
    func_ov004_02228300((UnkStruct_02228300 *) local.data, p2);
    result = func_0200e894(p1, &local);
    func_0200e91c(&local);
    return result;
}

void func_ov004_022282bc(UnkStruct_022282bc *p, unsigned long v)
{
    p->unk_00 = v;
}

void func_ov004_022282b8(UnkStruct_022282b8 *p, unsigned char v)
{
    p->unk_00 = v;
}

void func_ov004_022282b0(unsigned char *a, unsigned char *b)
{
    *b = *a;
}

void func_ov004_0222820c(unsigned char *self, unsigned char *p, int previous)
{
    int b, k;
    unsigned int h;
    b = *(int *) (p + 0xc);
    func_ov004_022282bc((UnkStruct_022282bc *) (self + 0x7d4), b);
    func_ov004_022282b8((UnkStruct_022282b8 *) (self + 0x8f0), (unsigned char) b);
    switch (*(int *) (p + 0xc)) {
        case 0:
            k = 0x38;
            break;
        case 1:
            k = 0x39;
            break;
        case 2:
            k = 0x3a;
            break;
    }
    func_020109a0(self, k, 3, 0);
    h = (unsigned int) (*(int *) (self + 0x2d4) << 4) >> 16;
    func_02056fcc(self + 0x2d0, h, 3, 0x1000, (unsigned short) (h - 1));
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
        func_ov004_0223b334(self + 0x5c, *(short *) (self + 0x8e));
    }
}

void func_ov004_022281e0(unsigned char *base, int arg2)
{
    unsigned char val;
    func_ov004_022282b0(base + 0x8f0, &val);
    func_ov004_022282c0((int) base, (unsigned char) val, 6, arg2);
}

void func_ov004_0222818c(UnkStruct_0222818c *self)
{
    if (func_02056f94(&self->unk_2D0) == 0) {
        return;
    }
    func_020109fc(self, 0x0, 3, 3);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        return;
    }
    self->unk_7FC = func_02008258(self, self->unk_7F0);
}

void func_ov004_02228170(void *self)
{
    func_02010f5c(self);
    func_02010d64(self);
    func_ov004_0222818c((UnkStruct_0222818c *) self);
}

void func_ov004_02228164(Struct0200A4AC *ptr, int a, unsigned char b, int c, int d)
{
    ptr->unk_00 = a;
    ptr->unk_04 = b;
    ptr->unk_08 = c;
    ptr->unk_0C = d;
}
