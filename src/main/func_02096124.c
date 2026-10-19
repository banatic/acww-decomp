/* func_02096124 @ 0x02096124, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200f290(int, int);

int func_02096124(int a, int b)
{
    int result = func_02096718(b);
    if (result != 0) {
        return func_0200f290(result, a);
    }
    return 0;
}
