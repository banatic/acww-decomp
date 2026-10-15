/* func_0200dbb4 @ 0x0200dbb4, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200dc00(void *, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_0200dbb4(void *a, int b, int c, int d)
{
    int stack0[3];
    int stack1[4];
    int result;

    func_0200e92c(stack0);
    func_0200e90c(stack0, 0, c, d);
    func_0200dc00(stack1, b);
    *(int *) ((char *) a + 0x7f4) = 0;
    result = func_0200e894(a, stack0);
    func_0200e91c(stack0);
    return result;
}
