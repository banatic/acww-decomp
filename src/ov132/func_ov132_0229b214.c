/* func_ov132_0229b214 @ 0x0229b214, 0x28 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov132_0229adfc(void *self);
extern unsigned char *func_ov002_02208098(void *self, unsigned char byte);

void func_ov132_0229b214(void *self)
{
    if (func_0208e484((char *) self + 0x94) != 0) {
        func_ov132_0229adfc(self);
        func_ov002_02208098(self, ((unsigned char *) self)[0x1503]);
    }
}
