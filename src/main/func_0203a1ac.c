/* func_0203a1ac @ 0x0203a1ac, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020399c8(void *self);
extern void func_0203990c(void *self);
extern void func_0203a330(void *p);
extern void func_0203a3ec(void *p);
extern void func_0208a1f4(void *p);
extern void func_0208af00(void *self);
extern void func_020edb3c(void *self);
extern int data_020da658;

void *func_0203a1ac(void *self)
{
    *(void **) self = (void *) &data_020da658;
    func_020399c8(self);
    func_0203990c(self);
    func_0203a330((char *) self + 0x88);
    func_0203a3ec((char *) self + 0x54);
    func_0208a1f4((char *) self + 0x30);
    func_0208a1f4((char *) self + 0x1c);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
