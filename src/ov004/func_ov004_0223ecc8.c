/* func_ov004_0223ecc8 @ 0x0223ecc8, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02032c50(void *);
extern void *func_020551e0(void *);
extern void *func_02055764(void *);
extern void *func_02089b38(void *);
extern int func_0209d104(void *);
extern void func_0209d340(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov004_0223eaec(void *);
extern void func_020012dc(void *arg0);

void *func_ov004_0223ecc8(char *self)
{
    // DECLS
    // ENDDECLS
    func_0209d104(self + 0x288);
    func_0209d340(self + 0x284);
    func_02055764(self + 0x1e8);
    func_02089b38(self + 0x19c);
    __cxa_vec_cleanup(self + 0x178, 0x2, 0xc, ((void (*)(void *)) func_020012dc));
    func_020551e0(self + 0xb0);
    func_02032c50(self + 0x68);
    func_ov004_0223eaec(self);
    return self;
}
