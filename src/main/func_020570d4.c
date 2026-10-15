/* func_020570d4 @ 0x020570d4, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020574b4(void *);
extern int func_02057468(void *, int, int);
extern int func_020573f0(void *, int, int, int);
extern void func_02057428(void *);
extern void func_020574b0(void *);

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
