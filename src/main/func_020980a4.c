/* func_020980a4 @ 0x020980a4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066688(void);
extern void func_02138c48(void *p, int a, int b, void (*handler)(void));

void *func_020980a4(void *p)
{
    func_02138c48(p, 10, 0x100, func_02066688);
    return p;
}
