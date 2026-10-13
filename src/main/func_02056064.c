/* func_02056064 @ 0x02056064, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020560e0(int a, int b);
extern int func_02056084(int a, int b);

int func_02056064(int a, int b)
{
    return func_020560e0(a, b) | func_02056084(a, b);
}
