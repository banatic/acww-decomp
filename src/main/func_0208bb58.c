/* func_0208bb58 @ 0x0208bb58, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208ba10(void *self);
extern void func_020b5618(void *ptr);
extern void func_0208a1f4(void *ptr);
extern void func_0208af00(void *self);
extern __arm void func_020edb3c(void *self);
extern char data_020e21fc;

void *func_0208bb58(void *self)
{
    *(void **) self = &data_020e21fc;
    func_0208ba10(self);
    func_020b5618((char *) self + 0x3c);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
