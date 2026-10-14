/* func_ov004_0220d840 @ 0x0220d840, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void func_ov004_0220d800(void *);
extern void func_ov004_0220d9a0();
extern void func_ov004_0220d9a4();

void *func_ov004_0220d840(char *self)
{
    // DECLS
    // ENDDECLS
    __cxa_vec_ctor(self + 0x4, 0x4, 0x10, (void *) func_ov004_0220d9a4, (void *) func_ov004_0220d9a0);
    func_ov004_0220d800(self);
    return self;
}
