/* func_0200c1b8 @ 0x0200c1b8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(int *);
extern void func_0200e90c(int *, int, int, int);
extern int func_0200e894(void *, int *);
extern void func_0200e91c(int *);

int func_0200c1b8(void *a, int b, int c)
{
    int local[8];
    int result;
    if (*(int *) ((char *) a + 0x704) != 0x12) {
        return 1;
    }
    func_0200e92c(local);
    func_0200e90c(local, 0x13, b, c);
    result = func_0200e894(a, local);
    func_0200e91c(local);
    return result;
}
