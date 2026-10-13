/* func_ov003_0221066c @ 0x0221066c, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(int, void *);
extern void func_0200e91c(void *);

int func_ov003_0221066c(int arg0, int arg1, int arg2)
{
    char buf[32];
    int result;

    func_0200e92c(buf);
    func_0200e90c(buf, 0x63, arg1, arg2);
    result = func_0200e894(arg0, buf);
    func_0200e91c(buf);
    return result;
}
