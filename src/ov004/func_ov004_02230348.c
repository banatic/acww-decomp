/* func_ov004_02230348 @ 0x02230348, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020551e0(void *);
extern void *func_020565b0(void *);
extern void func_ov004_0222c394(void *);
extern int func_ov004_0222c538(void *);
extern void *func_ov004_0222c7a0(void *);
extern void *data_ov004_02255538;

void *func_ov004_02230348(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255538;
    func_020565b0(self + 0x418);
    func_ov004_0222c394(self + 0x3ec);
    func_ov004_0222c538(self + 0x348);
    func_020551e0(self + 0x290);
    func_ov004_0222c7a0(self);
    return self;
}
