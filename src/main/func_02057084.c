/* func_02057084 @ 0x02057084, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020574b4(void *);
extern int func_02057468(void *, void *, void *);
extern int func_020573b8(void *, void *, void *, int);
extern void func_02057428(void *);
extern void func_020574b0(void *);

int func_02057084(void *p1, void *p2, void *p3, void *p4, int p5)
{
    char local[12];
    int result;

    func_020574b4(local);
    if (func_02057468(local, p1, p2)) {
        result = func_020573b8(local, p3, p4, p5);
        func_02057428(local);
        func_020574b0(local);
        return result;
    }
    func_020574b0(local);
    return 0;
}
