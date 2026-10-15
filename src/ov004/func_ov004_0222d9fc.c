/* func_ov004_0222d9fc @ 0x0222d9fc, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020324c4(void *);
extern void *func_020565b0(void *);
extern void *func_ov004_0222c7a0(void *);
extern void *data_ov004_02254e4c;

void *func_ov004_0222d9fc(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254e4c;
    func_020324c4(self + 0x3f4);
    func_020324c4(self + 0x358);
    func_020324c4(self + 0x2bc);
    func_020565b0(self + 0x290);
    func_ov004_0222c7a0(self);
    return self;
}
