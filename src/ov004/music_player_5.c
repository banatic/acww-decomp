/* music_player_5: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022168bc @ 0x022168bc, 0x1c bytes, Thumb
 * func_ov004_0221688c @ 0x0221688c, 0x30 bytes, Thumb
 * func_ov004_02216858 @ 0x02216858, 0x34 bytes, Thumb
 * func_ov004_02216820 @ 0x02216820, 0x38 bytes, Thumb
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_022517bc[];
extern void *const data_ov004_02251868[];
extern void *func_ov004_022110e4(void *p);
extern void *func_ov004_0220d110(void *p);
extern void *func_ov004_0220d0f4(void *p);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);

void *func_ov004_0221688c(char *self);

void func_ov004_022168bc(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x8a8)))) {
        func_ov004_0221688c((char *) conditionInput0);
    }
}

void *func_ov004_0221688c(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_022517bc;
    *(const void **) (self + 0xec) = data_ov004_02251868;
    func_ov004_0220d110(self + 0x848);
    return self;
}

void *func_ov004_02216858(char *self)
{
    *(const void **) (self) = data_ov004_022517bc;
    *(const void **) (self + 0xec) = data_ov004_02251868;
    func_ov004_0220d0f4(self + 0x848);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_02216820(char *self)
{
    *(const void **) (self) = data_ov004_022517bc;
    *(const void **) (self + 0xec) = data_ov004_02251868;
    func_ov004_0220d0f4(self + 0x848);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}
