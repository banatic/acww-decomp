/* func_ov004_0222cd50 @ 0x0222cd50, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020324c4(void *);
extern void func_02066994(void *);
extern void func_ov004_0222c7a0(void *);
extern void *data_ov004_02254c58;
extern void *data_ov004_02254cc8;

void *func_ov004_0222cd50(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02254c58;
    *(void **) (self + 0x290) = &data_ov004_02254cc8;
    func_020324c4(self + 0x2d8);
    func_02066994(self + 0x290);
    func_ov004_0222c7a0(self);
    return self;
}
