/* func_0200cc00 @ 0x0200cc00, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern void func_0200cc40(void *, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

int func_0200cc00(void *a, int b, int c, int d)
{
    char s1[12];
    char s2[16];
    int result;

    func_0200e92c(s1);
    func_0200e90c(s1, 4, c, d);
    func_0200cc40(s2, b);
    result = func_0200e894(a, s1);
    func_0200e91c(s1);
    return result;
}
