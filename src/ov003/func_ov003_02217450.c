/* func_ov003_02217450 @ 0x02217450, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void *func_ov003_02217450(void *a, void *b, void *c)
{
    void *stack[8];
    void *result;

    func_0200e92c(stack);
    func_0200e90c(stack, 0x45, b, c);
    result = func_0200e894(a, stack);
    func_0200e91c(stack);
    return result;
}
