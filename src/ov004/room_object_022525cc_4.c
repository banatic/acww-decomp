/* room_object_022525cc_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02219b1c @ 0x02219b1c, 0x1c bytes, Thumb
 * func_ov004_02219aec @ 0x02219aec, 0x30 bytes, Thumb
 * func_ov004_02219ab8 @ 0x02219ab8, 0x34 bytes, Thumb
 * func_ov004_02219a80 @ 0x02219a80, 0x38 bytes, Thumb
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_022525cc[];
extern void *const data_ov004_02252678[];
extern void *func_ov004_022110e4(void *p);
extern void *func_ov004_0220d110(void *p);
extern void *func_ov004_0220d0f4(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_02219aec(char *self);

void func_ov004_02219b1c(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x8a4)))) {
        func_ov004_02219aec((char *) conditionInput0);
    }
}

void *func_ov004_02219aec(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_022525cc;
    *(const void **) (self + 0xec) = data_ov004_02252678;
    func_ov004_0220d110(self + 0x84c);
    return self;
}

void *func_ov004_02219ab8(char *self)
{
    *(const void **) (self) = data_ov004_022525cc;
    *(const void **) (self + 0xec) = data_ov004_02252678;
    func_ov004_0220d0f4(self + 0x84c);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_02219a80(char *self)
{
    *(const void **) (self) = data_ov004_022525cc;
    *(const void **) (self + 0xec) = data_ov004_02252678;
    func_ov004_0220d0f4(self + 0x84c);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
