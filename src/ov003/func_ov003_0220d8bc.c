/* func_ov003_0220d8bc @ 0x0220d8bc, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern void func_0200e91c(void *);

void *func_ov003_0220d8bc(void *a, void *b, void *c)
{
    char local[0x20];
    void *result;

    func_0200e92c(local);
    func_0200e90c(local, 0x82, b, c);
    result = func_0200e894(a, local);
    func_0200e91c(local);
    return result;
}
