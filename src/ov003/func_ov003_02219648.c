/* func_ov003_02219648 @ 0x02219648, 0x1e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern void func_020109a0(int, int, int, int);

void func_ov003_02219648(void)
{
    int x;

    x = func_02096718(4);
    if (x != 0) {
        func_020109a0(x, 0x99, 3, 0);
    }
}
