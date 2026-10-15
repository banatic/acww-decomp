/* func_ov004_02237374 @ 0x02237374, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_022358c0(void *, int);
extern void func_ov004_02237134(void *);
extern void func_ov004_02237218(void *);

void *func_ov004_02237374(char *self)
{
    // DECLS
    // ENDDECLS
    if (*(int *) (self + 0x15c) == 0x26) {
        func_ov004_02237218(self);
    } else {
        if (*(int *) (self + 0x15c) == 0xc) {
            func_ov004_02237134(self);
        }
    }
    func_ov004_022358c0(self, 0x666);
    *(void **) (self + 0x158) = (char *) *(int *) (self + 0x158) + 0x1;
    return self + 0x158;
}
