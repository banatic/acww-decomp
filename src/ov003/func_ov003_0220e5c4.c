/* func_ov003_0220e5c4 @ 0x0220e5c4, 0x3a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_ov003_0220e5c4(void *a, int b, int c, int d)
{
    struct {
        char pad0[0xc];
        int field_c;
        char pad2[0xc];
    } local;
    int result;

    func_0200e92c(&local);
    func_0200e90c(&local, 0x74, c, d);
    local.field_c = b;
    result = func_0200e894(a, &local);
    func_0200e91c(&local);
    return result;
}
