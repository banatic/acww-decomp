/* func_ov101_0229d850 @ 0x0229d850, 0x24 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);
extern void func_ov002_0220af94(void);

void func_ov101_0229d850(void *self)
{
    asm {
        ldr r0, =0xb7c
        add r0, self, r0
    }
    func_ov094_0229a098();
    asm {
        ldr r0, =0x2810
        add r0, self, r0
    }
    func_ov002_0220af94();
}
