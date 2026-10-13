/* func_020b40dc @ 0x020b40dc, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b5418(void *p, void *q);
extern void func_020b54c8(void *p);
extern void func_020a9b50(void *p);
extern void func_020b4ca4(void *p);
extern void func_020b4ad4(void *p);
extern void func_020a8210(void);
extern void func_020a8228(void);
extern void func_020b550c(void);
extern void func_020b5524(void);
extern void func_02138d6c(void *p, int a, int b, void (*fp1)(void), void (*fp2)(void));
extern void MI_CpuFill8(void *p, int a, int b);

void *func_020b40dc(char *self)
{
    func_020b5418(self, self);
    func_020b54c8(self + 0x4c);
    func_020a9b50(self + 0xaf0);
    func_02138d6c(self + 0x14fc, 0xb, 0x5c, func_020a8228, func_020a8210);
    *(int *) (self + 0x18f0) = 0;
    func_020b4ca4(self + 0x18f4);
    func_020b4ad4(self + 0x1934);
    func_02138d6c(self + 0x1964, 0x10, 0x20, func_020b5524, func_020b550c);
    MI_CpuFill8(self + 0xafc, 0, 0xa00);
    return self;
}
