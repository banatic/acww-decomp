/* func_ov145_0229a3fc @ 0x0229a3fc, 0x32 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov145_022998f0(void *, unsigned char);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov145_02299e08(void *);

void func_ov145_0229a3fc(void *self)
{
    if (func_0208e484((char *) self + 0xc8) == 0) {
        return;
    }
    if (func_ov145_022998f0(self, *(unsigned char *) ((char *) self + 0xc2)) != 0) {
        return;
    }
    func_ov002_02208098((void *) (self), 3);
    func_ov145_02299e08(self);
}
