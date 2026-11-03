/* insurer_5: 9 functions, module ov071
 * mwccarm 1.2/base -O4,s
 * func_ov071_02279ea4 @ 0x02279ea4, 0x118 bytes, Thumb
 * func_ov071_02279e90 @ 0x02279e90, 0x14 bytes, Thumb
 * func_ov071_02279e30 @ 0x02279e30, 0x60 bytes, Thumb
 * func_ov071_02279dd8 @ 0x02279dd8, 0x58 bytes, Thumb
 * func_ov071_02279dac @ 0x02279dac, 0x2c bytes, Thumb
 * func_ov071_02279da4 @ 0x02279da4, 0x8 bytes, Thumb
 * func_ov071_02279d9c @ 0x02279d9c, 0x8 bytes, Thumb
 * func_ov071_02279d98 @ 0x02279d98, 0x4 bytes, Thumb
 * func_ov071_02279d94 @ 0x02279d94, 0x4 bytes, Thumb
 */

extern void *func_020edf70(unsigned int size);
extern void *func_0203f130(void *ptr);
extern void *func_0205467c(void *ptr);
extern void func_0201b394(void *ptr);
extern void *func_0201a430(void *ptr);
extern int func_020169a8(void *ptr);
extern int func_0201b324(void *ptr);
extern void func_0201af14(void *ptr);
extern void func_0201b370(void *ptr);
extern void func_0201adec(void *ptr);
extern void *func_0201a7ec(void *ptr);
extern void func_0201a794(void *ptr);
extern void *func_02032c64(void *ptr);
extern void *func_02089c88(void *ptr);
extern void *func_020f55cc(void *ptr);
extern void func_02013c2c(void *ptr);
extern void *func_02019eb0(void *ptr);
extern void func_0201489c(void *ptr);
extern void *func_02082f60(void *ptr);
extern void *func_ov071_02278fb8(void *ptr);
extern char data_020d8c64;
extern char data_020da088;
extern char data_ov071_0227a278;
extern int data_020c8120;
extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov071_02278f1c(void *a, void *b);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern void MI_CpuFill8(void *dest, unsigned char data, unsigned int size);
extern int func_0202ec58(int);
extern void func_02016764(int, int, int, int, int, int, int, int);
extern void func_02054188(int, int, int);
extern void func_ov071_02279d04(int, int);
extern int func_0202ec14(void *parameter0);
extern int func_02041620(void);
extern int func_0208602c(void);
extern int func_020860b8(int);
extern int func_0208786c(int);
extern int data_ov071_0227a1c4;
extern int data_ov071_0227a194;

void *func_ov071_02279ea4(void)
{
    void *self = func_020edf70(0x744);
    if (self) {
        func_0203f130(self);
        *(void **) self = &data_020d8c64;
        *(unsigned short *) ((char *) self + 0xea) = 0xfff1;
        func_0205467c((char *) self + 0xec);
        func_0201b394((char *) self + 0x2a0);
        func_0201a430((char *) self + 0x2ac);
        func_020169a8((char *) self + 0x334);
        func_0201b324((char *) self + 0x350);
        func_0201af14((char *) self + 0x3a8);
        func_0201b370((char *) self + 0x3aa);
        func_0201adec((char *) self + 0x3b0);
        func_0201a7ec((char *) self + 0x418);
        func_0201a794((char *) self + 0x420);
        func_02032c64((char *) self + 0x49c);
        func_02089c88((char *) self + 0x4cc);
        func_020f55cc((char *) self + 0x514);
        func_02013c2c((char *) self + 0x558);
        func_02019eb0((char *) self + 0x564);
        func_0201489c((char *) self + 0x618);
        *(void **) self = &data_020da088;
        func_02082f60((char *) self + 0x640);
        *(void **) self = &data_ov071_0227a278;
        func_ov071_02278fb8((char *) self + 0x658);
    }
    return self;
}

int func_ov071_02279e90(void)
{
    return data_020c8120 - 0x1000;
}

int func_ov071_02279e30(char *p)
{
    if (!func_0202edc8(p)) {
        return 0;
    }
    func_0201c280(p, p + 0x658);
    func_ov071_02278f1c(p + 0x658, p);
    func_0201af28(p + 0x350, 2, 0x200, 0x100, 0x100);
    MI_CpuFill8(p + 0x724, 0, 5);
    return 1;
}

int func_ov071_02279dd8(int self)
{
    if (!func_0202ec58(self)) {
        return 0;
    }

    func_02016764(self + 0x334, self, 0x141, 0, 0, 0x1000, 0, 1);
    func_02054188(self + 0xec, 0xc, 0xe);
    func_ov071_02279d04(self, 4);
    return 1;
}

int func_ov071_02279dac(void *arg0)
{
    if (func_0202ec14((void *) arg0) == 0) {
        return 0;
    }
    if (func_02041620() == 0) {
        func_0208786c((int) func_020860b8((int) func_0208602c()));
    }
    return 1;
}

int func_ov071_02279da4(void)
{
    return (int) &data_ov071_0227a1c4;
}

int func_ov071_02279d9c(void)
{
    return (int) &data_ov071_0227a194;
}

int func_ov071_02279d98(void)
{
    return 219;
}

int func_ov071_02279d94(void)
{
    return 107;
}
