/* func_ov004_02239c6c @ 0x02239c6c, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209d2b4(void *);
extern void func_020edf54(void *);
extern void func_020ee62c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void *);
extern void func_ov004_02239c28(void *);
extern void func_020b82d0();
extern void func_ov004_02239c5c();
extern void *data_020da13c;
extern void *data_ov004_02255ebc;

void *func_ov004_02239c6c(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255ebc;
    func_0209d2b4(self + 0x7f8);
    __cxa_vec_cleanup(self + 0x2a8, 0x2, 0x2a8, (void *) func_020b82d0);
    func_ov004_02239c28(self + 0x244);
    __cxa_vec_cleanup(self + 0x50, 0x5, 0x64, (void *) func_ov004_02239c5c);
    *(void **) (self) = &data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}
