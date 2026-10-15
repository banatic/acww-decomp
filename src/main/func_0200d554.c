/* func_0200d554 @ 0x0200d554, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_0200d554(int param0, int param1, int param2)
{
    int stack[8];
    int result;

    func_0200e92c(stack);
    func_0200e90c(stack, 1, param1, param2);
    result = func_0200e894((void *) param0, stack);
    func_0200e91c(stack);
    return result;
}
