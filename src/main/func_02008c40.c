/* func_02008c40 @ 0x02008c40, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern unsigned int *func_0200f27c(void *, int);
extern int func_0200e91c(void *);

int func_02008c40(void *p0, int p1, int p2)
{
    char local[0x20];
    func_0200e92c(local);
    func_0200e90c(local, 0x79, p1, p2);
    if (func_0200e894(p0, local)) {
        func_0200f27c(p0, 8);
        func_0200e91c(local);
        return 1;
    }
    func_0200e91c(local);
    return 0;
}
