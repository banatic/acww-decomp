/* func_ov003_0220edcc @ 0x0220edcc, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *p);
extern void func_0200e90c(void *p, int a, int b, int c);
extern int func_0200e894(int a, void *p);
extern void func_0200e91c(void *p);

int func_ov003_0220edcc(int arg1, int arg2, int arg3)
{
    int local[8];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 0x71, arg2, arg3);
    result = func_0200e894(arg1, local);
    func_0200e91c(local);
    return result;
}
