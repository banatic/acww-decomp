/* func_0206435c @ 0x0206435c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057970(int, int);
extern int func_020579b8(int, int);
extern int func_02057988(int, int);
extern int func_02057918(int, int);
extern int MI_CpuCopy8(int, int, int);

int func_0206435c(int a, int b, int c, int d)
{
    int A;
    int B;
    int C;
    int D;
    A = func_02057970(a, c);
    B = func_020579b8(b, d);
    C = func_02057988(b, B);
    D = func_02057918(b, B);
    return MI_CpuCopy8(A, C, D);
}
