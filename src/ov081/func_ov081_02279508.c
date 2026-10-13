/* func_ov081_02279508 @ 0x02279508, 0x118 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(unsigned int size);
extern void func_0203f130(void);
extern void func_0205467c(void *);
extern void func_0201b394(void *);
extern void func_0201a430(void *);
extern void func_020169a8(void *);
extern void func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void func_02032c64(void *);
extern void func_02089c88(void *);
extern void func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void func_02019eb0(void *);
extern void func_0201489c(void *);
extern void func_02082f60(void *);
extern void func_ov081_0227903c(void *);
extern char data_020d8c64;
extern char data_020da088;
extern char data_ov081_022797bc;

void *func_ov081_02279508(void)
{
    char *self;
    self = (char *) func_020edf70(0x728);
    if (self) {
        func_0203f130();
        *(void **) self = &data_020d8c64;
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
        *(void **) self = &data_020da088;
        func_02082f60(self + 0x640);
        *(void **) self = &data_ov081_022797bc;
        func_ov081_0227903c(self + 0x658);
    }
    return self;
}
