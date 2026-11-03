/* g3d_tex_copy: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206439c @ 0x0206439c, 0x3e bytes, Thumb
 * func_0206435c @ 0x0206435c, 0x3e bytes, Thumb
 */

extern int func_02057a20(int a, int b);
extern int func_02057a40(int a, int b);
extern int func_020579f0(int a, int b);
extern int func_020579c4(int a, int b);
extern void MI_CpuCopy8(int a, int b, int c);
extern int func_02057970(int, int);
extern int func_020579b8(int, int);
extern int func_02057988(int, int);
extern int func_02057918(int, int);

void func_0206439c(int p0, int p1, int p2, int p3)
{
    int t1, t2, t3, t4;
    t1 = func_02057a20(p0, p2);
    t2 = func_02057a40(p1, p3);
    t3 = func_020579f0(p1, t2);
    t4 = func_020579c4(p1, t2);
    MI_CpuCopy8(t1, t3, t4);
}

void func_0206435c(int a, int b, int c, int d)
{
    int A;
    int B;
    int C;
    int D;
    A = func_02057970(a, c);
    B = func_020579b8(b, d);
    C = func_02057988(b, B);
    D = func_02057918(b, B);
    MI_CpuCopy8(A, C, D);
}
