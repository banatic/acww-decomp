/* func_ov004_0222cd8c @ 0x0222cd8c, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020324fc(void *);
extern void *func_02066a30(void *);
extern void *func_ov004_0222c87c(void *);
extern void *data_ov004_02254c58;
extern void *data_ov004_02254cc8;

void *func_ov004_0222cd8c(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    func_02066a30(self + 0x290);
    *(void **) (self) = &data_ov004_02254c58;
    *(void **) (self + 0x290) = &data_ov004_02254cc8;
    func_020324fc(self + 0x2d8);
    return self;
}
