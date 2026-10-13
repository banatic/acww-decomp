/* func_ov047_02262700 @ 0x02262700, 0x118 bytes, Thumb, module ov047
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
extern void __arm func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void func_02019eb0(void *);
extern void func_0201489c(void *);
extern void func_02082f60(void *);
extern void func_ov047_02261990(void *);

extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov047_02262ca4[];

void *func_ov047_02262700(void)
{
    void *self = func_020edf70(0x740);
    if (self) {
        func_0203f130();
        *(void **) self = (void *) data_020d8c64;
        *(unsigned short *) ((char *) self + 0xEA) = 0xfff1;
        func_0205467c((char *) self + 0xEC);
        func_0201b394((char *) self + 0x2A0);
        func_0201a430((char *) self + 0x2AC);
        func_020169a8((char *) self + 0x334);
        func_0201b324((char *) self + 0x350);
        func_0201af14((char *) self + 0x3A8);
        func_0201b370((char *) self + 0x3AA);
        func_0201adec((char *) self + 0x3B0);
        func_0201a7ec((char *) self + 0x418);
        func_0201a794((char *) self + 0x420);
        func_02032c64((char *) self + 0x49C);
        func_02089c88((char *) self + 0x4CC);
        func_020f55cc((char *) self + 0x514);
        func_02013c2c((char *) self + 0x558);
        func_02019eb0((char *) self + 0x564);
        func_0201489c((char *) self + 0x618);
        *(void **) self = (void *) data_020da088;
        func_02082f60((char *) self + 0x640);
        *(void **) self = (void *) data_ov047_02262ca4;
        func_ov047_02261990((char *) self + 0x658);
    }
    return self;
}
