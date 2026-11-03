/* insect_catalog_3: 12 functions, module ov116
 * mwccarm 1.2/base -O4,s
 * func_ov116_0229e0e8 @ 0x0229e0e8, 0x56 bytes, Thumb
 * func_ov116_0229e0c0 @ 0x0229e0c0, 0x28 bytes, Thumb
 * func_ov116_0229e074 @ 0x0229e074, 0x4c bytes, Thumb
 * func_ov116_0229e010 @ 0x0229e010, 0x64 bytes, Thumb
 * func_ov116_0229dfc0 @ 0x0229dfc0, 0x50 bytes, Thumb
 * func_ov116_0229dfa8 @ 0x0229dfa8, 0x16 bytes, Thumb
 * func_ov116_0229df8c @ 0x0229df8c, 0x1c bytes, Thumb
 * func_ov116_0229df6c @ 0x0229df6c, 0x20 bytes, Thumb
 * func_ov116_0229df50 @ 0x0229df50, 0x1c bytes, Thumb
 * func_ov116_0229dee8 @ 0x0229dee8, 0x66 bytes, Thumb
 * func_ov116_0229dedc @ 0x0229dedc, 0xc bytes, Thumb
 * func_ov116_0229ded0 @ 0x0229ded0, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x94];
    void *sub;
    unsigned char pad_98[0x60];
    void *obj;
} UnkStruct_0229dee8;

extern int func_0208e484(void *arg);
extern int func_ov114_0229c60c(void *p);
extern int func_ov116_0229e4cc(void *self, int type);
extern int func_ov114_0229c2c8(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern unsigned char *func_ov116_0229ddd0(void *p);
extern void func_ov116_0229de10(void *);
extern int func_ov114_0229d2d8(char *p);
extern unsigned short data_021fbe40;
extern void func_ov114_0229d244(void *);
extern void func_ov114_0229d220(void *);
extern void func_ov114_0229d52c(void *, int);
extern int func_ov114_0229d1dc(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov116_0229deb4(void *arg0);
extern void func_ov002_02207fc0(void *);
extern int func_0206fe60(void);
extern void func_02070b84(char *p);
extern void func_ov114_0229c3ac(void *);
extern int func_ov114_0229c5f4(void *);
extern void func_ov002_0220a374(void *, int);
extern int func_ov114_0229c690(char *p);
extern int func_ov114_0229c628(int);

void func_ov116_0229dee8(UnkStruct_0229dee8 *self);
int func_ov116_0229dedc(char *p);
int func_ov116_0229ded0(int p0);

int func_ov116_0229e0e8(void *self)
{
    int result;

    if ((result = func_0208e484((char *) self + 0x94)) == 0) {
        return result;
    }
    result = func_ov114_0229c60c((char *) self + 0xf8);
    if (result != -1) {
        if ((result = func_ov116_0229e4cc(self, result)) != 0) {
            return result;
        }
    } else {
        if (func_ov114_0229c2c8((char *) self + 0xf8) != 0) {
            return (int) func_ov002_02208098(self, 6);
        }
    }
    func_ov002_02208098(self, 2);
    return (int) func_ov116_0229ddd0(self);
}

void func_ov116_0229e0c0(void *self)
{
    if (func_0208e484((char *) self + 0x94)) {
        func_ov116_0229de10(self);
        func_ov002_02208098(self, *(unsigned char *) ((char *) self + 0x142c));
    }
}

void func_ov116_0229e074(char *self)
{
    int res1, res2;
    if (func_ov114_0229d2d8(self + 0xf8)) {
        func_ov002_02208098((void *) self, 7);
    }
    func_ov114_0229d52c((void *) (self + 0xf8), *(unsigned int *) (self + 0x1424));
    res1 = func_ov116_0229dedc(self);
    res2 = func_ov116_0229ded0((int) self);
    func_ov002_0220a0b4((void *) (self + 0x94), res1, res2);
}

void func_ov116_0229e010(void *param)
{
    void *r5;
    void *r2;

    if (data_021fbe40 & 1) {
        func_ov114_0229d244((char *) param + 0xf8);
    } else {
        func_ov114_0229d220((char *) param + 0xf8);
        func_ov002_02208098(param, 8);
    }
    func_ov114_0229d52c((char *) param + 0xf8, *(int *) ((char *) param + 0x1424));
    r5 = (void *) func_ov116_0229dedc((char *) param);
    r2 = (void *) func_ov116_0229ded0((int) param);
    param = (char *) param + 0x94;
    func_ov002_0220a0b4(param, (int) r5, (int) r2);
}

void func_ov116_0229dfc0(char *p)
{
    if (func_ov114_0229d1dc(p + 0xf8)) {
        func_ov002_02208098(p, 2);
        func_ov116_0229ddd0(p);
    }
    func_ov114_0229d52c(p + 0xf8, *(int *) (p + 0x1424));
    {
        int a, b;
        a = func_ov116_0229dedc((char *) p);
        b = func_ov116_0229ded0((int) p);
        func_ov002_0220a0b4(p + 0x94, a, b);
    }
}

void func_ov116_0229dfa8(void *param0)
{
    func_ov116_0229deb4((void *) param0);
    func_ov002_02208098(param0, 0);
}

void func_ov116_0229df8c(void *arg0)
{
    func_ov116_0229dee8((UnkStruct_0229dee8 *) arg0);
    func_ov002_02207fc0(arg0);
    func_ov002_02208098(arg0, 2);
}

void func_ov116_0229df6c(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov116_0229dfa8((void *) r4);
    } else {
        func_ov116_0229df8c((void *) r4);
    }
}

void func_ov116_0229df50(char *p)
{
    p[0x142a] = 0;
    func_02070b84(p + 0x13b8);
}

void func_ov116_0229dee8(UnkStruct_0229dee8 *self)
{
    int r5;
    int r2;

    func_ov114_0229c3ac(&self->obj);
    r5 = func_ov116_0229dedc((char *) self);
    r2 = func_ov116_0229ded0((int) self);
    func_ov002_0220a0b4(&self->sub, r5, r2);
    if (func_ov114_0229c60c(&self->obj) != -1 || func_ov114_0229c5f4(&self->obj) != 0) {
        func_ov002_0220a374(&self->sub, 0xd);
    } else {
        func_ov002_0220a374(&self->sub, 1);
    }
    func_ov116_0229de10(self);
}

int func_ov116_0229dedc(char *p)
{
    return func_ov114_0229c690(p + 0xf8);
}

int func_ov116_0229ded0(int p0)
{
    return func_ov114_0229c628((p0 + 248));
}
