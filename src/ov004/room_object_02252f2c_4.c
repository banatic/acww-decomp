/* room_object_02252f2c_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0221a548 @ 0x0221a548, 0x1c bytes, Thumb
 * func_ov004_0221a518 @ 0x0221a518, 0x30 bytes, Thumb
 * func_ov004_0221a4e4 @ 0x0221a4e4, 0x34 bytes, Thumb
 * func_ov004_0221a4ac @ 0x0221a4ac, 0x38 bytes, Thumb
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_02252f2c[];
extern void *const data_ov004_02252fd8[];
extern void *func_ov004_022110e4(void *p);
extern void *func_ov004_0220d110(void *p);
extern void *func_ov004_0220d0f4(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_0221a518(char *self);

void func_ov004_0221a548(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x8a0)))) {
        func_ov004_0221a518((char *) conditionInput0);
    }
}

void *func_ov004_0221a518(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02252f2c;
    *(const void **) (self + 0xec) = data_ov004_02252fd8;
    func_ov004_0220d110(self + 0x848);
    return self;
}

void *func_ov004_0221a4e4(char *self)
{
    *(const void **) (self) = data_ov004_02252f2c;
    *(const void **) (self + 0xec) = data_ov004_02252fd8;
    func_ov004_0220d0f4(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_0221a4ac(char *self)
{
    *(const void **) (self) = data_ov004_02252f2c;
    *(const void **) (self + 0xec) = data_ov004_02252fd8;
    func_ov004_0220d0f4(self + 0x848);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
