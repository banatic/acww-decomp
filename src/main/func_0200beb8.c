/* func_0200beb8 @ 0x0200beb8, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void *func_0200beb8(void *param0, void *param1, void *param2)
{
    void *sp[8];
    void *result;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x15, param1, param2);
    result = func_0200e894(param0, sp);
    func_0200e91c(sp);
    return result;
}
