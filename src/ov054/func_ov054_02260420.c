/* func_ov054_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov054_02261f98(void *addr);
extern void func_0202ee5c(void *addr);
extern int data_ov054_02263094;

void *func_ov054_02260420(void *self)
{
    *(int *) self = (int) &data_ov054_02263094;
    func_ov054_02261f98((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
