/* func_ov051_022613a4 @ 0x022613a4, 0x118 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

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

extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];
extern unsigned char data_ov051_0226193c[];

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