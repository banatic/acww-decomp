/* func_ov105_0229e9a4 @ 0x0229e9a4, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229a098(void);
extern void func_ov002_0220af94(void);
extern int func_ov002_0220ab84(void *p, int param);

void func_ov105_0229e9a4(char *p)
{
    asm {
        ldr r0, =0xd84
        add r0, p, r0
    }
    func_ov094_0229a098();
    asm {
        ldr r0, =0x5fb8
        add r0, p, r0
    }
    func_ov002_0220af94();
    func_ov002_0220ab84(p + 0x5fb8, 0x21);
}
