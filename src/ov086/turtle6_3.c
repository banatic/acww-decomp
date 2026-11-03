/* turtle6_3: 5 functions, module ov086
 * mwccarm 1.2/base -O4,s
 * func_ov086_022790b8 @ 0x022790b8, 0x118 bytes, Thumb
 * func_ov086_02279088 @ 0x02279088, 0x30 bytes, Thumb
 * func_ov086_02279020 @ 0x02279020, 0x68 bytes, Thumb
 * func_ov086_02279018 @ 0x02279018, 0x8 bytes, Thumb
 * func_ov086_02279010 @ 0x02279010, 0x8 bytes, Thumb
 */

struct UnkStruct_02279020;

extern void *func_020edf70(unsigned int size);
extern void *func_0203f130(void *obj);
extern void *func_0205467c(void *p);
extern void func_0201b394(void *p);
extern void *func_0201a430(void *p);
extern int func_020169a8(void *p);
extern int func_0201b324(void *p);
extern void func_0201af14(void *p);
extern void func_0201b370(void *p);
extern void func_0201adec(void *p);
extern void *func_0201a7ec(void *p);
extern void func_0201a794(void *p);
extern void *func_02032c64(void *p);
extern void *func_02089c88(void *p);
extern void *func_020f55cc(void *p);
extern void func_02013c2c(void *p);
extern void *func_02019eb0(void *p);
extern void func_0201489c(void *p);
extern void *func_02082f60(void *p);
extern void *func_ov086_02278ec8(void *p);
extern char data_020d8c64;
extern char data_020da088;
extern char data_ov086_0227938c;
extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov086_02278e6c(void *, void *);
extern int func_0202ec58(void *arg0);
extern void func_ov086_02278f80(struct UnkStruct_02279020 *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);
extern int data_ov086_022792d8;
extern int data_ov086_022792a8;

void *func_ov086_022790b8(void)
{
    void *p = func_020edf70(0x710);
    if (p) {
        func_0203f130(p);
        *(void **) p = (void *) &data_020d8c64;
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
        *(void **) p = (void *) &data_020da088;
        func_02082f60((char *) p + 0x640);
        *(void **) p = (void *) &data_ov086_0227938c;
        func_ov086_02278ec8((char *) p + 0x658);
    }
    return p;
}

int func_ov086_02279088(void *obj)
{
    if (func_0202edc8(obj) == 0) {
        return 0;
    }
    func_0201c280(obj, (char *) obj + 0x658);
    func_ov086_02278e6c((char *) obj + 0x658, obj);
    return 1;
}

int func_ov086_02279020(struct UnkStruct_02279020 *self)
{
    if (func_0202ec58((void *) self) == 0) {
        return 0;
    }

    func_ov086_02278f80(self, 0);

    func_02016764((char *) self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);

    func_02054188((char *) self + 0xec, 0xc, 0xe);

    *(unsigned int *) ((char *) self + 0x4e8) |= 2;

    return 1;
}

int func_ov086_02279018(void)
{
    return (int) &data_ov086_022792d8;
}

int func_ov086_02279010(void)
{
    return (int) &data_ov086_022792a8;
}
