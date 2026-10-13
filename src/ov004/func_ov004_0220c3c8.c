/* func_ov004_0220c3c8 @ 0x0220c3c8, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_0224fc4c;
extern char data_ov004_0224fcc0;
extern void func_020b82d0(void *);
extern void func_020324c4(void *);
extern void func_02066994(void *);
extern void func_0203f080(void *);
extern void func_020edf54(void *);

char *func_ov004_0220c3c8(char *self)
{
    *(int *) self = (int) &data_ov004_0224fc4c;
    *(int *) (self + 0xec) = (int) &data_ov004_0224fcc0;
    func_020b82d0(self + 0x1d4);
    func_020324c4(self + 0x138);
    func_02066994(self + 0xec);
    func_0203f080(self);
    func_020edf54(self);
    return self;
}
