/* func_ov003_02218388 @ 0x02218388, 0x3e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200e91c(void *);
extern int func_0200e894(int, void *);

int func_ov003_02218388(int p1, int p2, int p3)
{
    char local[0x1c];
    char *p;
    int ret;

    func_0200e92c(local);
    p = &local[0xc];
    func_0200e90c(local, 0x3b, p2, p3);
    p[0] = 0;
    p[1] = 0;
    ret = func_0200e894(p1, local);
    func_0200e91c(local);
    return ret;
}
