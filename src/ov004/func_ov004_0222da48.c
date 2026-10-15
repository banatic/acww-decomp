/* func_ov004_0222da48 @ 0x0222da48, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020324fc(void *);
extern void func_020565c8(void *);
extern void *func_ov004_0222c87c(void *);
extern void *data_ov004_02254e4c;

void *func_ov004_0222da48(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    *(void **) (self) = &data_ov004_02254e4c;
    func_020565c8(self + 0x290);
    func_020324fc(self + 0x2bc);
    func_020324fc(self + 0x358);
    func_020324fc(self + 0x3f4);
    return self;
}
