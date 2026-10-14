/* func_ov052_02261a8c @ 0x02261a8c, 0x154 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void func_0203f130(void);
extern void func_0205467c(void *p);
extern void func_0201b394(void *p);
extern void func_0201a430(void *p);
extern void func_020169a8(void *p);
extern void func_0201b324(void *p);
extern void func_0201af14(void *p);
extern void func_0201b370(void *p);
extern void func_0201adec(void *p);
extern void func_0201a7ec(void *p);
extern void func_0201a794(void *p);
extern void func_02032c64(void *p);
extern void func_02089c88(void *p);
extern void func_020f55cc(void *p);
extern void func_02013c2c(void *p);
extern void func_02019eb0(void *p);
extern void func_0201489c(void *p);
extern void func_02082f60(void *p);
extern void func_ov052_02261140(void *p);
extern void func_02034ce0(void);
extern void func_020051b0(void);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*c)(void), void (*d)(void));
extern char data_020d8c64;
extern char data_020da088;
extern char data_ov052_02261f40;

void *func_ov052_02261a8c(void)
{
    unsigned char *self = (unsigned char *) func_020edf70(0x740);
    if (self == 0) {
        goto end;
    }
    func_0203f130();
    *(unsigned int *) self = (unsigned int) &data_020d8c64;
    *(unsigned short *) (self + 0xea) = 0xfff1;
    func_0205467c(self + 0xec);
    func_0201b394(self + 0x2a0);
    func_0201a430(self + 0x2ac);
    func_020169a8(self + 0x334);
    func_0201b324(self + 0x350);
    func_0201af14(self + 0x3a8);
    func_0201b370(self + 0x3aa);
    func_0201adec(self + 0x3b0);
    func_0201a7ec(self + 0x418);
    func_0201a794(self + 0x420);
    func_02032c64(self + 0x49c);
    func_02089c88(self + 0x4cc);
    func_020f55cc(self + 0x514);
    func_02013c2c(self + 0x558);
    func_02019eb0(self + 0x564);
    func_0201489c(self + 0x618);
    *(unsigned int *) self = (unsigned int) &data_020da088;
    func_02082f60(self + 0x640);
    *(unsigned int *) self = (unsigned int) &data_ov052_02261f40;
    func_ov052_02261140(self + 0x658);
    *(unsigned short *) (self + 0x71e) = 0xfff1;
    __cxa_vec_ctor(self + 0x720, 3, 2, func_02034ce0, func_020051b0);
    *(unsigned int *) (self + 0x728) = 0;
    *(unsigned int *) (self + 0x72c) = 0;
end:
    return self;
}
