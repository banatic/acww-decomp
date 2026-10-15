/* func_ov003_0221535c @ 0x0221535c, 0x36 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern void *func_0200e894(void *, void *);
extern int func_0200e91c(void *);

void *func_ov003_0221535c(void *r0, void *r1, void *r2)
{
    char sp[0x20];
    void *r4;

    func_0200e92c(sp);
    func_0200e90c(sp, 0x53, r1, r2);
    r4 = func_0200e894(r0, sp);
    func_0200e91c(sp);
    return r4;
}
