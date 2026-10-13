/* func_ov068_02275140 @ 0x02275140, 0x44 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov068_02277f3c;
extern void func_ov004_0222c394(void *);
extern void func_ov004_0222c538(void *);
extern void func_020551e0(void *);
extern void func_ov004_0222c7a0(void *);
extern void func_020edf54(void *);

void *func_ov068_02275140(void *self)
{
    *(void **) self = &data_ov068_02277f3c;
    func_ov004_0222c394((char *) self + 0x3f8);
    func_ov004_0222c538((char *) self + 0x354);
    func_020551e0((char *) self + 0x29c);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
