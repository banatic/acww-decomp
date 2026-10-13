/* func_ov003_0222d520 @ 0x0222d520, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02032c50(void *);
extern void func_020551e0(void *);
extern void func_02089af4(void *);
extern void func_0209d104(void *);
extern void func_0209d340(void *);
extern void func_02138c48(void *, int, int, void *);
extern void func_ov003_0222d218(void *);
extern void func_020012dc();

void *func_ov003_0222d520(char *self)
{
    // DECLS
    // ENDDECLS
    func_0209d340(self + 0x230);
    func_02138c48(self + 0x1ec, 0x2, 0xc, (void *) func_020012dc);
    func_0209d104(self + 0x130);
    func_02089af4(self + 0x108);
    func_020551e0(self + 0x50);
    func_02032c50(self + 0x20);
    func_ov003_0222d218(self);
    return self;
}
