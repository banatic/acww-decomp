/* func_02012014 @ 0x02012014, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d8c64;
extern int data_020d8414;
extern void func_02014898(void *);
extern void func_02019eac(void *);
extern void func_02013c28(void *);
extern void func_020f5914(void *);
extern void func_02089c70(void *);
extern void func_02032c50(void *);
extern void func_0201a790(void *);
extern void func_0201a7e8(void *);
extern void func_0201ade4(void *);
extern void func_0201b320(void *);
extern void func_02016998(void *);
extern void func_0201a3f8(void *);
extern void func_0201b390(void *);
extern void func_02054630(void *);
extern void func_0203f080(void *);
extern void func_020edf54(void *);

void *func_02012014(void *a0)
{
    unsigned char *self = (unsigned char *) a0;
    *(int *) self = (int) &data_020d8c64;
    func_02014898(self + 0x618);
    func_02019eac(self + 0x564);
    func_02013c28(self + 0x558);
    *(int *) (self + 0x514) = (int) &data_020d8414;
    func_020f5914(self + 0x514);
    func_02089c70(self + 0x4cc);
    func_02032c50(self + 0x49c);
    func_0201a790(self + 0x420);
    func_0201a7e8(self + 0x418);
    func_0201ade4(self + 0x3b0);
    func_0201b320(self + 0x350);
    func_02016998(self + 0x334);
    func_0201a3f8(self + 0x2ac);
    func_0201b390(self + 0x2a0);
    func_02054630(self + 0xec);
    func_0203f080(self);
    func_020edf54(self);
    return self;
}
