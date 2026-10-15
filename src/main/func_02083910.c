/* func_02083910 @ 0x02083910, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078a50(char *);
extern void func_02083cb4(void);

char *func_02083910(char *p)
{
    func_02078a50(p + 4);
    asm { add r0, p, #0 }
    func_02083cb4();
    return p;
}
