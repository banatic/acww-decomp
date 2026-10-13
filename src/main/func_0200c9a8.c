/* func_0200c9a8 @ 0x0200c9a8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void func_0200c9e8(void *, void *);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_0200c9a8(void *p0, void *p1, void *p2, void *p3)
{
    char local[0x1c];
    int result;

    func_0200e92c(local);
    func_0200e90c(local, 5, p2, p3);
    func_0200c9e8(local + 0xc, p1);
    result = func_0200e894(p0, local);
    func_0200e91c(local);
    return result;
}
