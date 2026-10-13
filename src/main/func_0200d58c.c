/* func_0200d58c @ 0x0200d58c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200d900(int a, int b);
extern void func_0200d5ac(int a, int *b);

void func_0200d58c(int a)
{
    int x = 0;
    x = func_0200d900(a, 0);
    func_0200d5ac(a, &x);
}
