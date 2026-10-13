/* func_02098024 @ 0x02098024, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int __arm func_02138d6c(int, int, int, void (*)(void), void (*)(void));
extern void func_02066688(void);
extern void func_02066694(void);

int func_02098024(int x)
{
    func_02138d6c(x, 10, 0x100, func_02066694, func_02066688);
    return x;
}
