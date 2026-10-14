/* func_ov124_0229f460 @ 0x0229f460, 0x30 bytes, Thumb, module ov124
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *self, int a, int b, void *fp1, void *fp2);
extern void func_ov002_0220b3c4(void *ptr);

extern void func_02070be8(void);
extern void func_02070c08(void);

void *func_ov124_0229f460(void *self)
{
    __cxa_vec_ctor(self, 1, 0x6c, (void *) func_02070c08, (void *) func_02070be8);
    func_ov002_0220b3c4((char *) self + 0x6c);
    return self;
}
