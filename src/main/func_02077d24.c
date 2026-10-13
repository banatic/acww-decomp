/* func_02077d24 @ 0x02077d24, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077c7c(void);
extern void func_02138c48(int, int, int, void (*)(void));

int func_02077d24(int a)
{
    func_02138c48(a, 0x20, 0x24, func_02077c7c);
    return a;
}
