/* func_ov109_0229d3e8 @ 0x0229d3e8, 0x24 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);
extern void func_ov002_0220af94(void);

void func_ov109_0229d3e8(void *self)
{
    asm {
        ldr r0, =0xb54
        add r0, self, r0
    }
    func_ov094_0229a098();
    asm {
        ldr r0, =0x27e8
        add r0, self, r0
    }
    func_ov002_0220af94();
}
