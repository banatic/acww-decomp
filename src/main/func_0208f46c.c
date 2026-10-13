/* func_0208f46c @ 0x0208f46c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208effc(void *);
extern void func_0208f628(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

extern unsigned char data_020e23a0[];

void *func_0208f46c(void *self)
{
    *(void **) self = (void *) data_020e23a0;
    func_0208effc(self);
    func_0208f628((char *) self + 0x4c);
    func_0208a1f4((char *) self + 0x30);
    func_0208a1f4((char *) self + 0x1c);
    func_0208af00(self);
    return self;
}
