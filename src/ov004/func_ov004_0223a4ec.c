/* func_ov004_0223a4ec @ 0x0223a4ec, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054e18(void *);
extern void func_0209d104(void *);
extern void func_0209d340(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_ov004_02239c28(void *);
extern void func_020012dc();
extern void *data_ov004_02255db4;

void *func_ov004_0223a4ec(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_02255db4;
    func_02138c48(self + 0x1d0, 0x2, 0xc, (void *) func_020012dc);
    func_0209d104(self + 0x168);
    func_0209d340(self + 0x166);
    func_02054e18(self + 0x64);
    func_ov004_02239c28(self + 0x4);
    return self;
}
