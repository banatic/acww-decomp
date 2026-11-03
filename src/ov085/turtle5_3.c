/* turtle5_3: 5 functions, module ov085
 * mwccarm 1.2/base -O4,s
 * func_ov085_02279250 @ 0x02279250, 0x118 bytes, Thumb
 * func_ov085_02279220 @ 0x02279220, 0x30 bytes, Thumb
 * func_ov085_0227918c @ 0x0227918c, 0x94 bytes, Thumb
 * func_ov085_02279184 @ 0x02279184, 0x8 bytes, Thumb
 * func_ov085_0227917c @ 0x0227917c, 0x8 bytes, Thumb
 */

extern void *func_020edf70(unsigned int size);
extern void *func_0203f130(void *arg0);
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
extern void *func_ov085_02278f14(void *ptr);
extern unsigned int data_020d8c64;
extern unsigned int data_020da088;
extern unsigned int data_ov085_022794f0;
extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov085_02278eb8(void *, void *);
extern int func_0202ec58(void *);
extern void func_ov085_022790ec(void *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);
extern unsigned char func_0203fdc4(int);
extern void func_020865d8(void *, int);
extern int func_0202ea80(int, int);
extern void func_02086794(void *);
extern int data_021f3aa4;
extern int data_ov085_02279438;
extern int data_ov085_02279408;

void *func_ov085_02279250(void)
{
    char *self = (char *) func_020edf70(0x72c);
    if (self != 0) {
        func_0203f130((void *) self);
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

        *(unsigned int *) self = (unsigned int) &data_ov085_022794f0;
        func_ov085_02278f14(self + 0x658);
    }

    return self;
}

int func_ov085_02279220(void *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov085_02278eb8((char *) self + 0x658, self);
    return 1;
}

int func_ov085_0227918c(void *self)
{
    void *g;

    if (func_0202ec58(self) == 0) {
        return 0;
    }

    func_ov085_022790ec(self, 0);
    func_02016764((char *) self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188((char *) self + 0xec, 0xc, 0xe);

    *((unsigned int *) ((char *) self + 0x4e8)) |= 2;
    *((unsigned char *) ((char *) self + 0x728)) = func_0203fdc4(0x11);

    g = (void *) &data_021f3aa4;
    func_020865d8(g, 1);

    if (func_0202ea80(0x1f, 0) == 0) {
        func_02086794(g);
    }

    return 1;
}

int func_ov085_02279184(void)
{
    return (int) &data_ov085_02279438;
}

int func_ov085_0227917c(void)
{
    return (int) &data_ov085_02279408;
}
