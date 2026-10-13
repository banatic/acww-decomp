/* func_ov004_02230394 @ 0x02230394, 0x54 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055210(void *);
extern void func_020565c8(void *);
extern void func_020b9e58(void *);
extern void func_ov004_0222c398(void *);
extern void func_ov004_0222c548(void *);
extern void func_ov004_0222c87c(void *);
extern void *data_ov004_02255538;

void *func_ov004_02230394(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_0222c87c(self);
    *(void **) (self) = &data_ov004_02255538;
    func_02055210(self + 0x290);
    func_ov004_0222c548(self + 0x348);
    func_ov004_0222c398(self + 0x3ec);
    func_020b9e58(self + 0x3f0);
    func_020565c8(self + 0x418);
    return self;
}
