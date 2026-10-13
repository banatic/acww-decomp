/* func_0208de9c @ 0x0208de9c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a144(void *);
extern void func_0208dd60(void *);
extern void func_0208e00c(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);
extern int data_020e226c;

void *func_0208de9c(void *self)
{
    *(void **) self = (void *) &data_020e226c;
    func_0208a144((char *) self + 0xc);
    func_0208dd60(self);
    func_0208e00c((char *) self + 0xbc);
    func_0208e00c((char *) self + 0xa0);
    func_0208e00c((char *) self + 0x84);
    func_0208e00c((char *) self + 0x68);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
