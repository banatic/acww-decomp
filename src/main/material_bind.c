/* material_bind: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02057124 @ 0x02057124, 0x6 bytes, Thumb
 * func_020570d4 @ 0x020570d4, 0x4e bytes, Thumb
 * func_02057084 @ 0x02057084, 0x4e bytes, Thumb
 */

extern int func_020574b4(void *);
extern int func_02057468(void *, int, int);
extern int func_020573f0(void *, int, int, int);
extern void func_02057428(void *);
extern void func_020574b0(void *);
extern int func_020573b8(void *, void *, void *, int);

signed char func_02057124(signed char *p)
{
    return p[4];
}

int func_020570d4(int a, int b, int c, int d, int e)
{
    int local[3];
    int result;

    func_020574b4(local);
    if (func_02057468(local, a, b) != 0) {
        result = func_020573f0(local, c, d, e);
        func_02057428(local);
        func_020574b0(local);
        return result;
    }
    func_020574b0(local);
    return 0;
}

int func_02057084(void *p1, void *p2, void *p3, void *p4, int p5)
{
    char local[12];
    int result;

    func_020574b4(local);
    if (func_02057468(local, (int) p1, (int) p2)) {
        result = func_020573b8(local, p3, p4, p5);
        func_02057428(local);
        func_020574b0(local);
        return result;
    }
    func_020574b0(local);
    return 0;
}
