/* func_020046b4 @ 0x020046b4, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020f2378(void);
extern char data_021fd1bc;

void func_020046b4(void)
{
    asm { ldr r0, =data_021fd1bc }
    func_020f2378();
}
