/* taxi_driver_3: 6 functions, module ov051
 * mwccarm 1.2/base -O4,s
 * func_ov051_022613a4 @ 0x022613a4, 0x118 bytes, Thumb
 * func_ov051_02261364 @ 0x02261364, 0x40 bytes, Thumb
 * func_ov051_0226131c @ 0x0226131c, 0x48 bytes, Thumb
 * func_ov051_02261300 @ 0x02261300, 0x1c bytes, Thumb
 * func_ov051_022612f8 @ 0x022612f8, 0x8 bytes, Thumb
 * func_ov051_022612f0 @ 0x022612f0, 0x8 bytes, Thumb
 */

typedef struct Main Main;

struct Main {
    void *vtable;
    char pad_04[0xea - 0x04];
    unsigned short unk_EA;
    char sub_ec[0x2a0 - 0xec];
    char sub_2a0[0x2ac - 0x2a0];
    char sub_2ac[0x334 - 0x2ac];
    char sub_334[0x350 - 0x334];
    char sub_350[0x3a8 - 0x350];
    char sub_3a8[0x3aa - 0x3a8];
    char sub_3aa[0x3b0 - 0x3aa];
    char sub_3b0[0x418 - 0x3b0];
    char sub_418[0x420 - 0x418];
    char sub_420[0x49c - 0x420];
    char sub_49c[0x4cc - 0x49c];
    char sub_4cc[0x514 - 0x4cc];
    char sub_514[0x558 - 0x514];
    char sub_558[0x564 - 0x558];
    char sub_564[0x618 - 0x564];
    char sub_618[0x640 - 0x618];
    char sub_640[0x658 - 0x640];
    char sub_658[0x71c - 0x658];
};

extern void *func_020edf70(unsigned int size);
extern void *func_0203f130(void *argument0);
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
extern void *func_ov051_02261070(void *);
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov051_0226193c[];
extern int func_0202edc8(void *obj);
extern void func_0201c280(void *a, void *b);
extern void func_ov051_0226101c(void *a, void *b);
extern void func_0201b38c(void *a, int b);
extern int func_0202ec58(void *);
extern void func_ov051_0226122c(void *, int);
extern void func_0203e334(void);
extern void *data_ov051_02261b80;
extern int func_0202ec14(void *argument0);
extern void func_0203e328(void);
extern int data_ov051_022617e0;
extern int data_ov051_022617b0;

void *func_ov051_022613a4(void)
{
    Main *self = (Main *) func_020edf70(0x71c);
    if (self == 0) {
        goto ret;
    }

    func_0203f130(self);
    self->vtable = (void *) data_020d8c64;
    self->unk_EA = 0xfff1;

    func_0205467c(self->sub_ec);
    func_0201b394(self->sub_2a0);
    func_0201a430(self->sub_2ac);
    func_020169a8(self->sub_334);
    func_0201b324(self->sub_350);
    func_0201af14(self->sub_3a8);
    func_0201b370(self->sub_3aa);
    func_0201adec(self->sub_3b0);
    func_0201a7ec(self->sub_418);
    func_0201a794(self->sub_420);
    func_02032c64(self->sub_49c);
    func_02089c88(self->sub_4cc);
    func_020f55cc(self->sub_514);
    func_02013c2c(self->sub_558);
    func_02019eb0(self->sub_564);
    func_0201489c(self->sub_618);

    self->vtable = (void *) data_020da088;
    func_02082f60(self->sub_640);

    self->vtable = (void *) data_ov051_0226193c;
    func_ov051_02261070(self->sub_658);

ret:
    return self;
}

int func_ov051_02261364(void *obj)
{
    if (func_0202edc8(obj) == 0) {
        return 0;
    }
    func_0201c280(obj, (char *) obj + 0x658);
    func_ov051_0226101c((char *) obj + 0x658, obj);
    func_0201b38c((char *) obj + 0x2a0, 0xfb);
    return 1;
}

int func_ov051_0226131c(void *param)
{
    if (func_0202ec58(param) == 0) {
        return 0;
    }
    data_ov051_02261b80 = param;
    func_ov051_0226122c(param, 0);
    *(int *) ((char *) param + 0x4e8) |= 2;
    func_0203e334();
    *(short *) ((char *) param + 0x718) = 0x29;
    return 1;
}

int func_ov051_02261300(void *argument0)
{
    if (func_0202ec14(argument0) == 0) {
        return 0;
    }
    func_0203e328();
    return 1;
}

int func_ov051_022612f8(void)
{
    return (int) &data_ov051_022617e0;
}

int func_ov051_022612f0(void)
{
    return (int) &data_ov051_022617b0;
}
