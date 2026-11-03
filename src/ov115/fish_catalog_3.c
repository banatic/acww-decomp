/* fish_catalog_3: 12 functions, module ov115
 * mwccarm 1.2/base -O4,s
 * func_ov115_0229e0e8 @ 0x0229e0e8, 0x56 bytes, Thumb
 * func_ov115_0229e0c0 @ 0x0229e0c0, 0x28 bytes, Thumb
 * func_ov115_0229e074 @ 0x0229e074, 0x4c bytes, Thumb
 * func_ov115_0229e010 @ 0x0229e010, 0x64 bytes, Thumb
 * func_ov115_0229dfc0 @ 0x0229dfc0, 0x50 bytes, Thumb
 * func_ov115_0229dfa8 @ 0x0229dfa8, 0x16 bytes, Thumb
 * func_ov115_0229df8c @ 0x0229df8c, 0x1c bytes, Thumb
 * func_ov115_0229df6c @ 0x0229df6c, 0x20 bytes, Thumb
 * func_ov115_0229df50 @ 0x0229df50, 0x1c bytes, Thumb
 * func_ov115_0229dee8 @ 0x0229dee8, 0x66 bytes, Thumb
 * func_ov115_0229dedc @ 0x0229dedc, 0xc bytes, Thumb
 * func_ov115_0229ded0 @ 0x0229ded0, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x94];
    unsigned char unk_94;
    unsigned char pad_95[0x63];
    int unk_F8;
    unsigned char pad_FC[0x1328];
    int unk_1424;
} UnkStruct_0229e074;

typedef struct {
    unsigned char pad_00[0x94];
    void *sub;
    unsigned char pad_98[0x60];
    void *obj;
} UnkStruct_0229dee8;

extern int func_0208e484(void *arg);
extern int func_ov114_0229c60c(void *p);
extern int func_ov115_0229e4cc(void *self, int type);
extern int func_ov114_0229c2c8(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern unsigned char *func_ov115_0229ddd0(void *p);
extern void func_ov115_0229de10(void *);
extern int func_ov114_0229d2d8(void *p);
extern void func_ov114_0229d52c(void *p, int v);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern unsigned short data_021fbe40;
extern void func_ov114_0229d244(void *);
extern void func_ov114_0229d220(void *);
extern int func_ov114_0229d1dc(void *);
extern void func_ov115_0229deb4(void *unused0);
extern void func_ov002_02207fc0(void *arg);
extern int func_0206fe60(void);
extern void func_02070b84(char *ptr);
extern void func_ov114_0229c3ac(void *);
extern int func_ov114_0229c5f4(void *);
extern void func_ov002_0220a374(void *, int);
extern int func_ov114_0229c690(int);
extern int func_ov114_0229c628(char *p);

void func_ov115_0229dee8(UnkStruct_0229dee8 *self);
int func_ov115_0229dedc(int p0);
int func_ov115_0229ded0(char *p);

int func_ov115_0229e0e8(void *self)
{
    int result;
    int status;

    if ((status = func_0208e484((char *) self + 0x94)) == 0) {
        return status;
    }
    result = func_ov114_0229c60c((char *) self + 0xf8);
    if (result != -1) {
        if ((status = func_ov115_0229e4cc(self, result)) != 0) {
            return status;
        }
    } else {
        if (func_ov114_0229c2c8((char *) self + 0xf8) != 0) {
            return (int) func_ov002_02208098(self, 6);
        }
    }
    func_ov002_02208098((void *) (self), 2);
    return (int) func_ov115_0229ddd0(self);
}

void func_ov115_0229e0c0(void *self)
{
    if (func_0208e484((char *) self + 0x94)) {
        func_ov115_0229de10(self);
        func_ov002_02208098((void *) (self), *(unsigned char *) ((char *) self + 0x142c));
    }
}

void func_ov115_0229e074(UnkStruct_0229e074 *self)
{
    int a, b;

    if (func_ov114_0229d2d8(&self->unk_F8) != 0) {
        func_ov002_02208098((void *) (self), 7);
    }
    func_ov114_0229d52c(&self->unk_F8, self->unk_1424);
    a = func_ov115_0229dedc((int) self);
    b = func_ov115_0229ded0((char *) self);
    func_ov002_0220a0b4(&self->unk_94, a, b);
}

void func_ov115_0229e010(void *obj)
{
    int a, b;
    if (data_021fbe40 & 1) {
        func_ov114_0229d244((char *) obj + 0xf8);
    } else {
        func_ov114_0229d220((char *) obj + 0xf8);
        func_ov002_02208098((void *) (obj), 8);
    }
    func_ov114_0229d52c((char *) obj + 0xf8, *(int *) ((char *) obj + 0x1424));
    a = func_ov115_0229dedc((int) obj);
    b = func_ov115_0229ded0((char *) obj);
    func_ov002_0220a0b4((char *) obj + 0x94, a, b);
}

void func_ov115_0229dfc0(void *self)
{
    if (func_ov114_0229d1dc((char *) self + 0xf8)) {
        func_ov002_02208098((void *) (self), 2);
        func_ov115_0229ddd0(self);
    }
    func_ov114_0229d52c((char *) self + 0xf8, *(int *) ((char *) self + 0x1424));
    func_ov002_0220a0b4((char *) self + 0x94, func_ov115_0229dedc((int) self), func_ov115_0229ded0((char *) self));
}

void func_ov115_0229dfa8(void *param0)
{
    func_ov115_0229deb4(param0);
    func_ov002_02208098((void *) (param0), 0);
}

void func_ov115_0229df8c(void *arg)
{
    func_ov115_0229dee8((UnkStruct_0229dee8 *) arg);
    func_ov002_02207fc0(arg);
    func_ov002_02208098((void *) (arg), 2);
}

void func_ov115_0229df6c(int arg)
{
    if (func_0206fe60()) {
        func_ov115_0229dfa8((void *) arg);
    } else {
        func_ov115_0229df8c((void *) arg);
    }
}

void func_ov115_0229df50(char *self)
{
    self[0x142a] = 0;
    func_02070b84(self + 0x13b8);
}

void func_ov115_0229dee8(UnkStruct_0229dee8 *self)
{
    int r5;
    int r2;

    func_ov114_0229c3ac(&self->obj);
    r5 = func_ov115_0229dedc((int) self);
    r2 = func_ov115_0229ded0((char *) self);
    func_ov002_0220a0b4(&self->sub, r5, r2);
    if (func_ov114_0229c60c(&self->obj) != -1 || func_ov114_0229c5f4(&self->obj) != 0) {
        func_ov002_0220a374(&self->sub, 0xd);
    } else {
        func_ov002_0220a374(&self->sub, 1);
    }
    func_ov115_0229de10(self);
}

int func_ov115_0229dedc(int p0)
{
    return func_ov114_0229c690((p0 + 248));
}

int func_ov115_0229ded0(char *p)
{
    return func_ov114_0229c628(p + 0xf8);
}
