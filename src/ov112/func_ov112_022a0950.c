/* func_ov112_022a0950 @ 0x022a0950, 0x2c bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e930(void *ptr);
extern void func_ov112_0229f270(void *self);
extern void func_ov112_0229fe50(void *self, int flag);

void func_ov112_022a0950(void *self)
{
    if (func_0208e930((void *) ((char *) self + 0x4234))) {
        func_ov112_0229f270(self);
        func_ov112_0229fe50(self, 0x1000);
    }
}
