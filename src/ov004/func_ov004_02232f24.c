/* func_ov004_02232f24 @ 0x02232f24, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02004280(void *);
extern int func_02055f1c(void *);
extern void func_ov004_0223226c(void *object);
extern int func_ov004_02232314(void *);
extern int func_ov004_022323b0(void *);
extern void func_ov004_02232508(void *);
extern void func_ov004_02232794(void *);
extern void *data_ov004_022589fc;

int func_ov004_02232f24(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02232794(self + 0x128);
    func_ov004_0223226c(self + 0x34fc);
    func_ov004_02232314(self + 0x3460);
    func_ov004_02232508(self + 0x1228);
    func_ov004_022323b0(self + 0x3328);
    func_02055f1c(self + 0x50);
    *(void **) ((char *) &data_ov004_022589fc) = 0x0;
    func_02004280(self + 0x3534);
    return 0x1;
}
