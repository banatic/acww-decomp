/* func_ov003_0220efc8 @ 0x0220efc8, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void *func_ov003_0220efc8(void *a, void *b, void *c)
{
    char sp[0x20];
    void *r4;
    void *r5;
    void *r6;

    r5 = a;
    r4 = b;
    r6 = c;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x6e, r4, r6);
    r4 = func_0200e894(r5, sp);
    func_0200e91c(sp);
    return r4;
}
