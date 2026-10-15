/* func_0202ee5c @ 0x0202ee5c, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082f48(void *);
extern void func_02014898(void *);
extern void func_02019eac(void *);
extern void func_02013c28(void *);
extern void func_020f5914(void *);
extern void *func_02089c70(void *);
extern void *func_02032c50(void *);
extern void func_0201a790(void *);
extern void func_0201a7e8(void *);
extern void func_0201ade4(void *);
extern void func_0201b320(void *);
extern int func_02016998(void *);
extern void *func_0201a3f8(void *);
extern void func_0201b390(void *);
extern void *func_02054630(void *);
extern void *func_0203f080(void *);

extern unsigned char data_020d8414[];
extern unsigned char data_020d8c64[];
extern unsigned char data_020da088[];

void *func_0202ee5c(void *self)
{
    *(void **) self = (void *) data_020da088;
    func_02082f48((char *) self + 0x640);
    *(void **) self = (void *) data_020d8c64;
    func_02014898((char *) self + 0x618);
    func_02019eac((char *) self + 0x564);
    func_02013c28((char *) self + 0x558);
    *(void **) ((char *) self + 0x514) = (void *) data_020d8414;
    func_020f5914((char *) self + 0x514);
    func_02089c70((char *) self + 0x4cc);
    func_02032c50((char *) self + 0x49c);
    func_0201a790((char *) self + 0x420);
    func_0201a7e8((char *) self + 0x418);
    func_0201ade4((char *) self + 0x3b0);
    func_0201b320((char *) self + 0x350);
    func_02016998((char *) self + 0x334);
    func_0201a3f8((char *) self + 0x2ac);
    func_0201b390((char *) self + 0x2a0);
    func_02054630((char *) self + 0xec);
    func_0203f080(self);
    return self;
}
