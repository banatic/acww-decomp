/* func_ov004_0223eb1c @ 0x0223eb1c, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d2b4(void *);
extern void func_020edf54(void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_02089b38();
extern void *data_020da13c;
extern void *data_ov004_022562c0;

void *func_ov004_0223eb1c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022562c0;
    func_0209d2b4(self + 0x180);
    __cxa_vec_cleanup(self + 0x50, 0x4, 0x4c, (void *) func_02089b38);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
