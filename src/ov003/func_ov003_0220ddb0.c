/* func_ov003_0220ddb0 @ 0x0220ddb0, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *obj);
extern void func_0200e90c(void *obj, int size, int a, int b);
extern int func_0200e894(void *a, void *obj);
extern void func_0200e91c(void *obj);

int func_ov003_0220ddb0(void *a, int b, int c)
{
    char local[0x20];
    int ret;
    func_0200e92c(local);
    func_0200e90c(local, 0x80, b, c);
    ret = func_0200e894(a, local);
    func_0200e91c(local);
    return ret;
}
