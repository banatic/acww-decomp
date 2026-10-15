/* func_0205de70 @ 0x0205de70, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205de10(int a);
extern int func_0205ddfc(int a);
extern void func_02055b50(int a, int b);
extern int func_021077e8(int a) __attribute__((arm));

void func_0205de70(int a)
{
    int tmp;
    tmp = func_021077e8(func_0205de10(a));
    func_02055b50(func_0205ddfc(a), tmp);
}
