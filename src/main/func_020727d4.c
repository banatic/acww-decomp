/* func_020727d4 @ 0x020727d4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020725ec(char *p);
extern void func_02072574(char *p);

char *func_020727d4(char *p)
{
    func_020725ec(p + 4);
    func_02072574(p);
    return p;
}
