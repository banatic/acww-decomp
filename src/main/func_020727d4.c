/* func_020727d4 @ 0x020727d4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020725ec(char *p);
extern void func_02072574(void);

char *func_020727d4(char *p)
{
    func_020725ec(p + 4);
    asm { add r0, p, #0 }
    func_02072574();
    return p;
}
