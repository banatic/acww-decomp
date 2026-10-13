/* func_ov004_0221e308 @ 0x0221e308, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202e5e0(void *);
extern void func_02084f84(void *);
extern void func_ov004_0221ebf4(void *);
extern void *data_ov004_022539cc;

void *func_ov004_0221e308(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov004_022539cc;
    func_02084f84(self + 0x8b4);
    func_ov004_0221ebf4(self + 0x8a0);
    func_0202e5e0(self);
    return self;
}
