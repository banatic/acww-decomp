/* func_02080190 @ 0x02080190, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807a8(int, int);
extern int func_020951bc(int);
extern int func_02081c00(int);
extern int func_02081bc4(int, int);

int func_02080190(int a1, int a2, int a3)
{
    int p;
    p = func_020807a8(a1, a3);
    if (p && func_020951bc(a3) && func_02081c00(p)) {
        return func_02081bc4(p, a2);
    }
}
