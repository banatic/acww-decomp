/* func_ov125_022a0334 @ 0x022a0334, 0x24 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov125_022a0358(void);
extern void func_ov124_0229ef4c(void *, int);
extern void func_ov002_0220af94(void);

void func_ov125_022a0334(void *self)
{
    func_ov125_022a0358();
    func_ov124_0229ef4c((char *) self + 0x94, 4);
    asm {
        ldr r0, =0x6a8
        add r0, self, r0
    }
    func_ov002_0220af94();
}
