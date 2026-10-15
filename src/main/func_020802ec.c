/* func_020802ec @ 0x020802ec, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807a8(int, int);
extern int func_020951bc(int);
extern int func_02081d20(int);
extern void *func_02095074(int, int);
extern void func_02081c94(int, int);

void func_020802ec(int a0, int a1, int a2)
{
    int v = func_020807a8(a0, a2);
    if (!(v != 0 && func_020951bc(a2) != 0 && func_02081d20(v) > -10)) {
        func_02095074(a2, a1);
    } else {
        func_02081c94(v, a1);
    }
}
