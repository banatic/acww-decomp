/* func_02070444 @ 0x02070444, 0x4a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208b500(void);
extern int func_0208d12c(void *);
extern void func_02070490(int);
extern void func_0207055c(int, int);

void func_02070444(unsigned char *p, int player)
{
    int x;

    x = p[0] - 13;
    if (x == 0) {
        if (func_0208d12c((void *) func_0208b500()) != 0) {
            return;
        }
        func_02070490(x);
        func_0207055c(18, 4);
    } else {
        if (func_0208d12c((void *) func_0208b500()) == 0) {
            return;
        }
        func_02070490(x);
        x += 18;
        func_0207055c((unsigned char) x, 4);
    }
}
