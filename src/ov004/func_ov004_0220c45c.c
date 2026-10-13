/* func_ov004_0220c45c @ 0x0220c45c, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f130(void *self);
extern void func_02066a30(void *p);
extern void func_020324fc(void *p);
extern void func_020b82ec(void *p);
extern int data_ov004_02256c00;

extern unsigned char data_ov004_0224fc4c[];
extern unsigned char data_ov004_0224fcc0[];

void *func_ov004_0220c45c(void *self)
{
    func_0203f130(self);
    func_02066a30((char *) self + 0xec);
    *(int *) ((char *) self + 0) = (unsigned int) data_ov004_0224fc4c;
    *(int *) ((char *) self + 0xec) = (unsigned int) data_ov004_0224fcc0;
    func_020324fc((char *) self + 0x138);
    func_020b82ec((char *) self + 0x1d4);
    data_ov004_02256c00 = 0;
    return self;
}
