/* room_object_glowing_4: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022123a8 @ 0x022123a8, 0x1c bytes, Thumb
 * func_ov004_02212378 @ 0x02212378, 0x30 bytes, Thumb
 * func_ov004_02212344 @ 0x02212344, 0x34 bytes, Thumb
 * func_ov004_0221230c @ 0x0221230c, 0x38 bytes, Thumb
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_022509ac[];
extern void *const data_ov004_02250a58[];
extern void *func_ov004_022110e4(void *p);
extern void *func_ov004_0220d110(void *p);
extern void *func_ov004_0220d0f4(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_02212378(char *self);

void func_ov004_022123a8(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x8a0)))) {
        func_ov004_02212378((char *) conditionInput0);
    }
}

void *func_ov004_02212378(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_022509ac;
    *(const void **) (self + 0xec) = data_ov004_02250a58;
    func_ov004_0220d110(self + 0x844);
    return self;
}

void *func_ov004_02212344(char *self)
{
    *(const void **) (self) = data_ov004_022509ac;
    *(const void **) (self + 0xec) = data_ov004_02250a58;
    func_ov004_0220d0f4(self + 0x844);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_0221230c(char *self)
{
    *(const void **) (self) = data_ov004_022509ac;
    *(const void **) (self + 0xec) = data_ov004_02250a58;
    func_ov004_0220d0f4(self + 0x844);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
