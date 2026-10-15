/* func_ov003_02235f10 @ 0x02235f10, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02235f2c(void *element);
extern void __cxa_vec_cleanup(void *a, int b, int c, void (*d)(void *));

void *func_ov003_02235f10(void *self)
{
    __cxa_vec_cleanup(self, 0x10, 0x22, func_ov003_02235f2c);
    return self;
}
