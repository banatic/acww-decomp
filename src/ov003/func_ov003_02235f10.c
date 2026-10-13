/* func_ov003_02235f10 @ 0x02235f10, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02235f2c(void);
extern void func_02138c48(void *a, int b, int c, void (*d)(void));

void *func_ov003_02235f10(void *self)
{
    func_02138c48(self, 0x10, 0x22, func_ov003_02235f2c);
    return self;
}
