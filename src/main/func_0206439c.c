/* func_0206439c @ 0x0206439c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057a20(int a, int b);
extern int func_02057a40(int a, int b);
extern int func_020579f0(int a, int b);
extern int func_020579c4(int a, int b);
extern int MI_CpuCopy8(int a, int b, int c);

int func_0206439c(int p0, int p1, int p2, int p3)
{
    int t1, t2, t3, t4;
    t1 = func_02057a20(p0, p2);
    t2 = func_02057a40(p1, p3);
    t3 = func_020579f0(p1, t2);
    t4 = func_020579c4(p1, t2);
    return MI_CpuCopy8(t1, t3, t4);
}
