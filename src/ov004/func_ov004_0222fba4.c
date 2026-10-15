/* func_ov004_0222fba4 @ 0x0222fba4, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020324c4(void *);
extern void *func_02066994(void *);
extern void *func_020b82d0(void *);
extern void func_020edf54(void *);
extern void *func_ov004_0222c7a0(void *);
extern void *data_ov004_022553d8;
extern void *data_ov004_02255454;

void *func_ov004_0222fba4(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022553d8;
    *(void **) (self + 0x290) = &data_ov004_02255454;
    func_020b82d0(self + 0x374);
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    func_020edf54(self);
    return self;
}
