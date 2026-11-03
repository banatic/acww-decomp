/* fortune_teller_4: 7 functions, module ov045
 * mwccarm 1.2/base -O4,s
 * func_ov045_02261090 @ 0x02261090, 0x118 bytes, Thumb
 * func_ov045_02261034 @ 0x02261034, 0x5c bytes, Thumb
 * func_ov045_02260fe8 @ 0x02260fe8, 0x4c bytes, Thumb
 * func_ov045_02260fc4 @ 0x02260fc4, 0x24 bytes, Thumb
 * func_ov045_02260f94 @ 0x02260f94, 0x30 bytes, Thumb
 * func_ov045_02260f8c @ 0x02260f8c, 0x8 bytes, Thumb
 * func_ov045_02260f84 @ 0x02260f84, 0x8 bytes, Thumb
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
extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov045_02260c94(void *, void *);
extern void func_0201c3f4(void *, int);
extern void func_0203edf4(void *, int);
extern int func_0202ec58(void *p);
extern void func_ov045_02260e50(void *p, int x);
extern void *data_ov045_022615a0;
extern int func_0202ec14(void *argument0);
extern int func_0201b790(void *argument0);
extern int func_02055d0c(void *dst, const void *src, int size);
extern void func_ov004_022304bc(void);
extern int data_ov045_0226143c;
extern int data_ov045_022613dc;

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

int func_ov045_02261034(void *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x68c);
    func_ov045_02260c94((char *) self + 0x68c, self);
    func_0201c3f4(self, 0x100);
    func_0203edf4(self, 0x5000);
    *(int *) ((char *) self + 0x654) = -1;
    *(unsigned char *) ((char *) self + 0x758) = 0;
    return 1;
}

int func_ov045_02260fe8(void *p)
{
    if (func_0202ec58(p) == 0) {
        return 0;
    }

    data_ov045_022615a0 = p;
    func_ov045_02260e50(p, 0);

    *((unsigned int *) ((char *) p + 0x4e8)) |= 2;
    *((unsigned char *) p + 0x744) = 0xff;
    *((unsigned char *) p + 0x745) = 0xff;

    return 1;
}

int func_ov045_02260fc4(void *argument0)
{
    if (!func_0202ec14(argument0)) {
        return 0;
    }
    (*(int *) &data_ov045_022615a0) = 0;
    return 1;
}

int func_ov045_02260f94(void *arg)
{
    if (!func_0201b790(arg)) {
        return 0;
    }

    (void) ((void *) func_02055d0c((char *) arg + 0xec, (char *) arg + 0x65c, 0xe));
    func_ov004_022304bc();
    return 1;
}

int func_ov045_02260f8c(void)
{
    return (int) &data_ov045_0226143c;
}

int func_ov045_02260f84(void)
{
    return (int) &data_ov045_022613dc;
}
