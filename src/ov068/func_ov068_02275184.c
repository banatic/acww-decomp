/* func_ov068_02275184 @ 0x02275184, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_02277f3c;
extern void func_ov004_0222c394(char *);
extern void func_ov004_0222c538(char *);
extern void func_020551e0(char *);
extern void func_ov004_0222c7a0(char *);

char *func_ov068_02275184(char *self)
{
    *(char **) self = &data_ov068_02277f3c;
    func_ov004_0222c394(self + 0x3f8);
    func_ov004_0222c538(self + 0x354);
    func_020551e0(self + 0x29c);
    func_ov004_0222c7a0(self);
    return self;
}
