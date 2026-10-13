/* func_ov003_02215494 @ 0x02215494, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern void func_0200e91c(void *);

void *func_ov003_02215494(void *r0, void *r1, void *r2)
{
    void *sp[8];
    void *r4;
    void *r5;
    void *r6;

    r5 = r0;
    r4 = r1;
    r6 = r2;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x52, r4, r6);
    r4 = func_0200e894(r5, sp);
    func_0200e91c(sp);
    return r4;
}
