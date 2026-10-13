/* func_0209a8a4 @ 0x0209a8a4, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ac04(void);
extern void func_0209ad9c(int, int);
extern void func_0209b56c(void);

void func_0209a8a4(int r0)
{
    int r4 = r0;
    if (func_0209ac04() != 0) {
        func_0209ad9c(r4, 0);
        func_0209b56c();
    }
}
