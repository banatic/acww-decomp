/* func_ov045_02261090 @ 0x02261090, 0x118 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
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
extern void *func_ov045_02260d4c(void *ptr);

extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov045_022614f0[];

void *func_ov045_02261090(void)
{
    char *self;
    self = (char *) func_020edf70(0x75c);
    if (self == 0) {
        goto out;
    }
    func_0203f130(self);
    *(void **) self = (void *) data_020d8c64;
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
    *(void **) self = (void *) data_020da088;
    func_02082f60(self + 0x640);
    *(void **) self = (void *) data_ov045_022614f0;
    func_ov045_02260d4c(self + 0x68c);
out:
    return self;
}
