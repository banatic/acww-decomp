/* func_ov003_022188d0 @ 0x022188d0, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov003_02218918(void *, int, int, int);
extern int func_0200e894(int, void *);
extern void func_0200e91c(void *);

int func_ov003_022188d0(int a, int b, int c, int d, int e, short f)
{
    struct {
        int data[3];
    } loc1;
    struct {
        int data[5];
    } loc2;
    int ret;

    func_0200e92c(&loc1);
    func_0200e90c(&loc1, 0x38, e, f);
    func_ov003_02218918(&loc2, b, c, d);
    ret = func_0200e894(a, &loc1);
    func_0200e91c(&loc1);
    return ret;
}
