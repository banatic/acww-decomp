/* func_02072808 @ 0x02072808, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02072600(void *ptr);
extern void func_0207252c(void);
extern void func_020727b8(void);

void func_02072808(void *arg)
{
    func_02072600((char *) arg + 4);
    asm { add r0, arg, #0 }
    func_0207252c();
    asm { add r0, arg, #0 }
    func_020727b8();
}
