/* room_object_02251690_2: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_022133dc @ 0x022133dc, 0x1c bytes, Thumb
 * func_ov004_022133ac @ 0x022133ac, 0x30 bytes, Thumb
 * func_ov004_02213378 @ 0x02213378, 0x34 bytes, Thumb
 * func_ov004_02213340 @ 0x02213340, 0x38 bytes, Thumb
 * func_ov004_02213328 @ 0x02213328, 0x18 bytes, Thumb
 */

extern int func_ov004_0221152c(unsigned int size);
extern void *const data_ov004_02251690[];
extern void *const data_ov004_0225173c[];
extern void *func_ov004_022110e4(void *p);
extern void func_020f6560(void *p);
extern void func_020f655c(void *self);
extern void *func_ov004_02210cf0(void *p);
extern void func_ov004_02211518(void *p);
extern void func_02004094(void *);

void *func_ov004_022133ac(char *self);

void func_ov004_022133dc(void)
{
    char *conditionInput0;

    if ((conditionInput0 = (char *) (func_ov004_0221152c(0x850)))) {
        func_ov004_022133ac((char *) conditionInput0);
    }
}

void *func_ov004_022133ac(char *self)
{
    func_ov004_022110e4(self);
    *(const void **) (self) = data_ov004_02251690;
    *(const void **) (self + 0xec) = data_ov004_0225173c;
    func_020f6560(self + 0x844);
    return self;
}

void *func_ov004_02213378(char *self)
{
    *(const void **) (self) = data_ov004_02251690;
    *(const void **) (self + 0xec) = data_ov004_0225173c;
    func_020f655c(self + 0x844);
    func_ov004_02210cf0(self);
    return self;
}

void *func_ov004_02213340(char *self)
{
    *(const void **) (self) = data_ov004_02251690;
    *(const void **) (self + 0xec) = data_ov004_0225173c;
    func_020f655c(self + 0x844);
    func_ov004_02210cf0(self);
    func_ov004_02211518(self);
    return self;
}

int func_ov004_02213328(char *self)
{
    // DECLS
    // ENDDECLS
    func_02004094(self + 0x844);
    return 0x1;
}
