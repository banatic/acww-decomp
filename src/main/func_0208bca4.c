/* func_0208bca4 @ 0x0208bca4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208be84(int, int);
extern int func_0206f56c(void);
extern void func_0208bc88(int);

void func_0208bca4(int arg)
{
    int r4;
    int r0;

    r4 = func_0208be84(arg, 1);
    r0 = func_0206f56c();
    if (r4 != 0 || r0 != 0) {
        func_0208bc88(arg);
    }
}
