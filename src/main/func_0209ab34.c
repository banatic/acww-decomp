/* func_0209ab34 @ 0x0209ab34, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ad9c(char *a, int b);
extern int func_0207cb9c(int *a, int b, int c);
extern int func_0208150c(int a);
extern void func_0209b4d8(int a, int b, int c, int d);
extern void func_02003728(char *a, int b);
extern int data_021e5a2c[];

void func_0209ab34(char *A)
{
    int zero = 0;
    int t0, t1;
    t0 = func_0209ad9c(A, zero);
    t1 = func_0207cb9c(data_021e5a2c, zero, zero);
    func_0209b4d8(t0, 14, zero, func_0208150c(t1));
    func_02003728(A + 0x60, func_0208150c(t1));
}
