/* func_ov004_0222fc3c @ 0x0222fc3c, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020324fc(void *);
extern void *func_02066a30(void *);
extern void *func_020b82ec(void *);
extern void *func_ov004_0222c87c(void *);
extern void *data_ov004_022553d8;
extern void *data_ov004_02255454;

void *func_ov004_0222fc3c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    func_02066a30(self + 0x290);
    *(void **) (self) = &data_ov004_022553d8;
    *(void **) (self + 0x290) = &data_ov004_02255454;
    func_020324fc(self + 0x2d8);
    func_020b82ec(self + 0x374);
    return self;
}
