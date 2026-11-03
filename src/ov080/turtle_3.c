/* turtle_3: 6 functions, module ov080
 * mwccarm 1.2/base -O4,s
 * func_ov080_02279060 @ 0x02279060, 0x118 bytes, Thumb
 * func_ov080_02279030 @ 0x02279030, 0x30 bytes, Thumb
 * func_ov080_02278fb8 @ 0x02278fb8, 0x78 bytes, Thumb
 * func_ov080_02278fa0 @ 0x02278fa0, 0x18 bytes, Thumb
 * func_ov080_02278f98 @ 0x02278f98, 0x8 bytes, Thumb
 * func_ov080_02278f90 @ 0x02278f90, 0x8 bytes, Thumb
 */

extern void *func_020edf70(unsigned int);
extern void *func_0203f130(void *);
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
extern void *func_ov080_02278e48(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov080_022792ec[];
extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov080_02278dec(void *a, void *b);
extern int func_0202ec58(void *arg0);
extern void func_ov080_02278f00(void *p, int a);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g, int h);
extern void func_02054188(void *a, int b, int c);
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern void func_0203e2ec(void);
extern int func_0202ec14(void *parameter0);
extern int data_ov080_02279238;
extern int data_ov080_02279208;

void *func_ov080_02279060(void)
{
    void *s = func_020edf70(0x710);
    if (s != 0) {
        func_0203f130(s);
        *(int *) s = (int) (unsigned int) data_020d8c64;
        *(unsigned short *) ((char *) s + 0xea) = 0xfff1;
        func_0205467c((char *) s + 0xec);
        func_0201b394((char *) s + 0x2a0);
        func_0201a430((char *) s + 0x2ac);
        func_020169a8((char *) s + 0x334);
        func_0201b324((char *) s + 0x350);
        func_0201af14((char *) s + 0x3a8);
        func_0201b370((char *) s + 0x3aa);
        func_0201adec((char *) s + 0x3b0);
        func_0201a7ec((char *) s + 0x418);
        func_0201a794((char *) s + 0x420);
        func_02032c64((char *) s + 0x49c);
        func_02089c88((char *) s + 0x4cc);
        func_020f55cc((char *) s + 0x514);
        func_02013c2c((char *) s + 0x558);
        func_02019eb0((char *) s + 0x564);
        func_0201489c((char *) s + 0x618);
        *(int *) s = (int) (unsigned int) data_020da088;
        func_02082f60((char *) s + 0x640);
        *(int *) s = (int) (unsigned int) data_ov080_022792ec;
        func_ov080_02278e48((char *) s + 0x658);
    }
    return s;
}

int func_ov080_02279030(void *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, (char *) p + 0x658);
    func_ov080_02278dec((char *) p + 0x658, p);
    return 1;
}

int func_ov080_02278fb8(void *p)
{
    if (func_0202ec58((void *) p) == 0) {
        return 0;
    }
    func_ov080_02278f00(p, 0);
    func_02016764((char *) p + 0x334, p, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188((char *) p + 0xec, 0xc, 0xe);
    (*(unsigned int *) ((char *) p + 0x4e8)) |= 2;
    if (func_02099020(func_020984e8(), 1) == 0) {
        func_0203e2ec();
    }
    return 1;
}

int func_ov080_02278fa0(void *arg0)
{
    int result;
    if (func_0202ec14((void *) arg0) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

int func_ov080_02278f98(void)
{
    return (int) &data_ov080_02279238;
}

int func_ov080_02278f90(void)
{
    return (int) &data_ov080_02279208;
}
