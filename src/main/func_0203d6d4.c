/* func_0203d6d4 @ 0x0203d6d4, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203dd9c(void *a, void *b);
extern void *func_0203de48(void *a);
extern void func_020a7a04(void *a);
extern void *func_020a8228(void *);
extern void *func_020a8210(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void MI_CpuFill8(void *dst, int val, unsigned int n);

void *func_0203d6d4(void *self)
{
    func_0203dd9c(self, self);
    func_0203de48((char *) self + 0x5c);
    func_020a7a04((char *) self + 0x300);
    *(int *) ((char *) self + 0x50c) = -1;
    __cxa_vec_ctor((void *) ((char *) self + 0x510), 0xb, 0x5c, (((void (*)(void *)) func_020a8228)),
                   (((void (*)(void *)) func_020a8210)));
    MI_CpuFill8((char *) self + 0x30c, 0, 0x200);
    return self;
}
