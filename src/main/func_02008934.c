/* func_02008934 @ 0x02008934, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

int func_02008934(void *a, unsigned char b, int c, int d)
{
    struct {
        unsigned char data[0x1c];
    } local;
    int result;
    func_0200e92c(&local);
    func_0200e90c(&local, 0x84, c, d);
    local.data[0xc] = b;
    result = func_0200e894(a, &local);
    func_0200e91c(&local);
    return result;
}
