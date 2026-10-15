/* func_0205d058 @ 0x0205d058, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205cfd4(int a);
extern int func_0205d210(int b);
extern int func_0205d208(void);
extern int func_02064af4(int a, int b, int c);

void func_0205d058(int a, int b)
{
    int tmp1;
    int tmp2;
    tmp1 = func_0205cfd4(a);
    tmp2 = func_0205d210(b);
    func_02064af4(tmp2, tmp1, func_0205d208());
}
