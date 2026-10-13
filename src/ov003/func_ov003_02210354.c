/* func_ov003_02210354 @ 0x02210354, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern void func_0200e91c(void *);

void *func_ov003_02210354(void *p0, void *p1, void *p2)
{
    char local[0x20];
    void *result;

    func_0200e92c(local);
    func_0200e90c(local, 0x64, p1, p2);
    result = func_0200e894(p0, local);
    func_0200e91c(local);
    return result;
}
