/* func_ov003_0220e05c @ 0x0220e05c, 0x4a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, void *, void *);
extern int func_0200e894(void *, void *);
extern void func_0200f27c(void *, int);
extern void func_0200e91c(void *);

int func_ov003_0220e05c(void *a, void *b, void *c)
{
    char buf[0x20];
    func_0200e92c(buf);
    func_0200e90c(buf, 0x78, b, c);
    if (func_0200e894(a, buf)) {
        func_0200f27c(a, 7);
        func_0200e91c(buf);
        return 1;
    } else {
        func_0200e91c(buf);
        return 0;
    }
}
