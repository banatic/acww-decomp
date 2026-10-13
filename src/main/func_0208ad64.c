/* func_0208ad64 @ 0x0208ad64, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e20ac;
extern void func_0208a4dc(void *);
extern void func_0208aeb8(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);

void *func_0208ad64(void *self)
{
    ((void **) self)[0] = (void *) &data_020e20ac;
    func_0208a4dc(self);
    func_0208aeb8((char *) self + 0x90);
    func_0208aeb8((char *) self + 0x60);
    func_0208a1f4((char *) self + 0x20);
    func_0208a1f4((char *) self + 0x0c);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
