/* func_0200a6a0 @ 0x0200a6a0, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200a6f0(void *, void *, void *);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_0200a6a0(void *a, int *b, void *c, int d, short e)
{
    int local0[2];
    char local1[12];
    char local2[16];
    func_0200e92c(&local1);
    func_0200e90c(&local1, 0x1b, d, e);
    local0[0] = b[0];
    local0[1] = b[1];
    func_0200a6f0(&local2, local0, c);
    {
        int result = func_0200e894(a, &local1);
        func_0200e91c(&local1);
        return result;
    }
}
