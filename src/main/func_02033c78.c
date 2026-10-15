/* func_02033c78 @ 0x02033c78, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203428c(int, int, int);
extern int func_0202fc18(int, int, int, int, int);

int func_02033c78(int a0, int a1, int a2, int a3, int arg5, int arg6, int arg7)
{
    func_0203428c(a0 + 0x38, arg6, arg7);
    func_0202fc18(a0, a1, a2, a3, arg5);
    return 1;
}
