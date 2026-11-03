/* tv_8: 6 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02215f70 @ 0x02215f70, 0x1c bytes, Thumb
 * func_ov004_02215f40 @ 0x02215f40, 0x30 bytes, Thumb
 * func_ov004_02215f10 @ 0x02215f10, 0x30 bytes, Thumb
 * func_ov004_02215edc @ 0x02215edc, 0x34 bytes, Thumb
 * func_ov004_02215ea4 @ 0x02215ea4, 0x38 bytes, Thumb
 * func_ov004_02215e70 @ 0x02215e70, 0x34 bytes, Thumb
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_02251438[];
extern void *const data_ov004_022514e4[];
extern void *func_ov004_022110e4(void *p);
extern char *func_ov004_0220d268(void *p);
extern int func_ov004_0220d258(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_02215f10(char *self);

void func_ov004_02215f70(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x868)))) {
        func_ov004_02215f10((char *) conditionInput0);
    }
}

void *func_ov004_02215f40(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251438;
    *(const void **) (self + 0xec) = data_ov004_022514e4;
    func_ov004_0220d268(self + 0x848);
    return self;
}

void *func_ov004_02215f10(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251438;
    *(const void **) (self + 0xec) = data_ov004_022514e4;
    func_ov004_0220d268(self + 0x848);
    return self;
}

void *func_ov004_02215edc(char *self)
{
    *(const void **) (self) = data_ov004_02251438;
    *(const void **) (self + 0xec) = data_ov004_022514e4;
    func_ov004_0220d258(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_02215ea4(char *self)
{
    *(const void **) (self) = data_ov004_02251438;
    *(const void **) (self + 0xec) = data_ov004_022514e4;
    func_ov004_0220d258(self + 0x848);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

void *func_ov004_02215e70(char *self)
{
    *(const void **) (self) = data_ov004_02251438;
    *(const void **) (self + 0xec) = data_ov004_022514e4;
    func_ov004_0220d258(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}
