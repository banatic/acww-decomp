/* func_ov078_02279794 @ 0x02279794, 0x118 bytes, Thumb, module ov078
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int);
extern void func_0203f130(void *);
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
extern void func_ov078_02279010(void *);

extern int data_020d8c64;
extern int data_020da088;
extern int data_ov078_02279b2c;

void *func_ov078_02279794(void)
{
    void *p;

    p = func_020edf70(0x714);
    if (p != 0) {
        func_0203f130(p);
        *(unsigned long *) p = (unsigned long) &data_020d8c64;
        *(unsigned short *) ((char *) p + 0xea) = 0xfff1;
        func_0205467c((char *) p + 0xec);
        func_0201b394((char *) p + 0x2a0);
        func_0201a430((char *) p + 0x2ac);
        func_020169a8((char *) p + 0x334);
        func_0201b324((char *) p + 0x350);
        func_0201af14((char *) p + 0x3a8);
        func_0201b370((char *) p + 0x3aa);
        func_0201adec((char *) p + 0x3b0);
        func_0201a7ec((char *) p + 0x418);
        func_0201a794((char *) p + 0x420);
        func_02032c64((char *) p + 0x49c);
        func_02089c88((char *) p + 0x4cc);
        func_020f55cc((char *) p + 0x514);
        func_02013c2c((char *) p + 0x558);
        func_02019eb0((char *) p + 0x564);
        func_0201489c((char *) p + 0x618);
        *(unsigned long *) p = (unsigned long) &data_020da088;
        func_02082f60((char *) p + 0x640);
        *(unsigned long *) p = (unsigned long) &data_ov078_02279b2c;
        func_ov078_02279010((char *) p + 0x658);
    }
    return p;
}
