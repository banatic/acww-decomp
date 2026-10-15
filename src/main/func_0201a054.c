/* func_0201a054 @ 0x0201a054, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a3e8(int a0);
extern void func_02056658(int a1, int a2);
extern int func_020566a0(int a1, int a2, int a3);
extern void func_02056610(int a1, int a2);

int func_0201a054(int a0, int a1, int a2, int a3)
{
    if (func_0201a3e8(a0)) {
        func_02056658(a1, a2);
        if (func_020566a0(a1, a2, a3)) {
            return 1;
        }
        func_02056610(a1, a2);
    }
    return 0;
}
