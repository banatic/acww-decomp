/* func_ov076_0227947c @ 0x0227947c, 0x118 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d8c64;
extern int data_020da088;
extern int data_ov076_022797d4;
extern void *func_020edf70(int);
extern void *func_0203f130(void *arg0);
extern void *func_0205467c(void *);
extern void func_0201b394(void *);
extern void *func_0201a430(void *);
extern int func_020169a8(void *);
extern int func_0201b324(void *);
extern void func_0201af14(void *);
extern void func_0201b370(void *);
extern void func_0201adec(void *);
extern void *func_0201a7ec(void *);
extern void func_0201a794(void *);
extern void *func_02032c64(void *);
extern void *func_02089c88(void *);
extern void *func_020f55cc(void *);
extern void func_02013c2c(void *);
extern void *func_02019eb0(void *);
extern void func_0201489c(void *);
extern void *func_02082f60(void *);
extern void *func_ov076_02278e90(void *);

void *func_ov076_0227947c(void)
{
    void *self = func_020edf70(0x728);
    if (self != 0) {
        func_0203f130((void *) self);
        *(void **) self = (void *) &data_020d8c64;
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
        *(void **) self = (void *) &data_020da088;
        func_02082f60((char *) self + 0x640);
        *(void **) self = (void *) &data_ov076_022797d4;
        func_ov076_02278e90((char *) self + 0x658);
    }
    return self;
}
