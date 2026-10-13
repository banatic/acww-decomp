/* func_ov004_0223eb64 @ 0x0223eb64, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d2b4(void *);
extern void func_020ee62c(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_02089b38();
extern void *data_020da13c;
extern void *data_ov004_022562c0;

void *func_ov004_0223eb64(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022562c0;
    func_0209d2b4(self + 0x180);
    func_02138c48(self + 0x50, 0x4, 0x4c, (void *) func_02089b38);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    return self;
}
