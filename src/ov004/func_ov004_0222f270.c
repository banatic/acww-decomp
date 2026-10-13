/* func_ov004_0222f270 @ 0x0222f270, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0222f320(void *p);
extern void func_ov004_0222c600(void *self, int a, int b);
extern void func_02055dc8(void *p, void *fn, void *self);
extern void func_ov004_0222f2f4(void);
extern void func_ov004_0222f1b4(void *self);

int func_ov004_0222f270(void *self)
{
    void *p;

    p = func_ov004_0222f320(*(void **) ((char *) self + 8));
    func_ov004_0222c600(self, *(int *) ((char *) p + 8), *(int *) ((char *) p + 0xc));
    func_02055dc8((char *) self + 0xec, (void *) func_ov004_0222f2f4, self);
    func_ov004_0222f1b4(self);
    return 1;
}
