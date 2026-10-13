/* func_02048698 @ 0x02048698, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int __arm func_020644cc(int);
extern void func_02048cb8(int, int, int, int, int, int, int);
extern void func_02048f54(void);

void func_02048698(int a0, int a1, int a2, int a3)
{
    int r = func_020644cc(a2);
    int s = func_020644cc(a3);
    func_02048cb8(a0, a1, r + 1, s + 1, 29, (int) func_02048f54, 0);
}
