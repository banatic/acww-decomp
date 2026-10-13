/* func_0208d2e8 @ 0x0208d2e8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a144(void *);
extern void func_0208d15c(void *);
extern void func_0208e00c(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

extern char data_020e2218;

void *func_0208d2e8(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_020e2218;
    func_0208a144((char *) self + 0xc);
    func_0208d15c(self);
    func_0208e00c((char *) self + 0x88);
    func_0208e00c((char *) self + 0x6c);
    func_0208e00c((char *) self + 0x50);
    func_0208e00c((char *) self + 0x34);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    return self;
}
