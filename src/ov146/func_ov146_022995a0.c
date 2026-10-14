/* func_ov146_022995a0 @ 0x022995a0, 0x54 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a5e4(void *p);
extern void func_ov002_0220b0f4(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*cb)(void));
extern void func_02070be8(void);
extern void func_ov002_02209cb4(void *p);
extern void func_ov002_0220826c(void *p);
extern unsigned int data_ov146_0229b680;

void *func_ov146_022995a0(void *self)
{
    *(unsigned int *) self = (unsigned int) &data_ov146_0229b680;
    func_ov002_0220a5e4((char *) self + 0x1fb4);
    func_ov002_0220b0f4((char *) self + 0x1ee8);
    __cxa_vec_cleanup((char *) self + 0x1630, 0x14, 0x6c, func_02070be8);
    func_ov002_02209cb4((char *) self + 0x15cc);
    func_ov002_0220826c(self);
    return self;
}
