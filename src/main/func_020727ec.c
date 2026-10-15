/* func_020727ec @ 0x020727ec, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02072578(char *p);
extern void *func_020725f0(char *p);
extern void func_02072808(char *p);

char *func_020727ec(char *p)
{
    func_02072578(p);
    func_020725f0(p + 4);
    func_02072808(p);
    return p;
}
