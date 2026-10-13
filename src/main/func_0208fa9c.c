/* func_0208fa9c @ 0x0208fa9c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2400;
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);

void *func_0208fa9c(void *self)
{
    *(void **) self = (void *) &data_020e2400;
    func_0208a1f4((char *) self + 12);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
