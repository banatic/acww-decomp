/* mystery_cat_3: 7 functions, module ov074
 * mwccarm 1.2/base -O4,s
 * func_ov074_022798b4 @ 0x022798b4, 0x124 bytes, Thumb
 * func_ov074_022798a8 @ 0x022798a8, 0xc bytes, Thumb
 * func_ov074_02279878 @ 0x02279878, 0x30 bytes, Thumb
 * func_ov074_02279840 @ 0x02279840, 0x38 bytes, Thumb
 * func_ov074_02279814 @ 0x02279814, 0x2c bytes, Thumb
 * func_ov074_02279810 @ 0x02279810, 0x4 bytes, Thumb
 * func_ov074_02279808 @ 0x02279808, 0x8 bytes, Thumb
 */

typedef struct {
    void *vtbl;
    char pad_04[0xea - 0x04];
    unsigned short unk_EA;
    char unk_EC[0x2a0 - 0xec];
    char unk_2A0[0x2ac - 0x2a0];
    char unk_2AC[0x334 - 0x2ac];
    char unk_334[0x350 - 0x334];
    char unk_350[0x3a8 - 0x350];
    char unk_3A8[0x3aa - 0x3a8];
    char unk_3AA[0x3b0 - 0x3aa];
    char unk_3B0[0x418 - 0x3b0];
    char unk_418[0x420 - 0x418];
    char unk_420[0x49c - 0x420];
    char unk_49C[0x4cc - 0x49c];
    char unk_4CC[0x514 - 0x4cc];
    char unk_514[0x558 - 0x514];
    char unk_558[0x564 - 0x558];
    char unk_564[0x618 - 0x564];
    char unk_618[0x640 - 0x618];
    char unk_640[0x658 - 0x640];
    char unk_658[0x714 - 0x658];
    char unk_714[0x740 - 0x714];
} Struct_ov074_022798b4;

extern void *func_020edf70(unsigned int size);
extern void *func_0203f130(void *obj);
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
extern void *func_ov074_02278ffc(void *ptr);
extern void *func_ov074_02278b20(void *ptr);
extern char data_020d8c64;
extern char data_020da088;
extern char data_ov074_02279c68;
extern int data_020c8120;
extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov074_02278fa8(void *, void *);
extern int func_0202ec58(void *unused0);
extern void func_ov074_02278af8(void *a, void *b, void *c);
extern void func_ov074_02279778(void *a, int b);
extern unsigned char data_021fbe94[];
extern int func_0202ec14(void *argument0);
extern void func_ov074_02278a6c(int, int);
extern int data_ov074_02279ba0;

void *func_ov074_022798b4(void)
{
    Struct_ov074_022798b4 *obj = (Struct_ov074_022798b4 *) func_020edf70(0x740);
    if (obj == 0) {
        goto done;
    }
    func_0203f130(obj);
    obj->vtbl = &data_020d8c64;
    obj->unk_EA = 0xfff1;
    func_0205467c(obj->unk_EC);
    func_0201b394(obj->unk_2A0);
    func_0201a430(obj->unk_2AC);
    func_020169a8(obj->unk_334);
    func_0201b324(obj->unk_350);
    func_0201af14(obj->unk_3A8);
    func_0201b370(obj->unk_3AA);
    func_0201adec(obj->unk_3B0);
    func_0201a7ec(obj->unk_418);
    func_0201a794(obj->unk_420);
    func_02032c64(obj->unk_49C);
    func_02089c88(obj->unk_4CC);
    func_020f55cc(obj->unk_514);
    func_02013c2c(obj->unk_558);
    func_02019eb0(obj->unk_564);
    func_0201489c(obj->unk_618);
    obj->vtbl = &data_020da088;
    func_02082f60(obj->unk_640);
    obj->vtbl = &data_ov074_02279c68;
    func_ov074_02278ffc(obj->unk_658);
    func_ov074_02278b20(obj->unk_714);
done:
    return obj;
}

int func_ov074_022798a8(void)
{
    return data_020c8120;
}

int func_ov074_02279878(char *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, p + 0x658);
    func_ov074_02278fa8(p + 0x658, p);
    return 1;
}

int func_ov074_02279840(void *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    func_ov074_02278af8((char *) self + 0x714, *(void **) data_021fbe94, (char *) self + 0xec);
    func_ov074_02279778(self, 3);
    return 1;
}

int func_ov074_02279814(int param)
{
    if (func_0202ec14((void *) param) == 0) {
        return 0;
    }
    func_ov074_02278a6c(param + 0x714, (*(int *) data_021fbe94));
    return 1;
}

int func_ov074_02279810(void)
{
    return 0;
}

int func_ov074_02279808(void)
{
    return (int) &data_ov074_02279ba0;
}
