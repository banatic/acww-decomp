/* func_ov003_0221f5f4 @ 0x0221f5f4, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020565b0(void);
extern void func_02138c48(void *p, int a, int b, void (*cb)(void));
extern void func_02055764(void *p);

void *func_ov003_0221f5f4(void *self)
{
    func_02138c48((char *) self + 0xb4, 2, 0x20, func_020565b0);
    func_02055764(self);
    return self;
}
