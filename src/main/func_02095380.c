/* func_02095380 @ 0x02095380, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_0200f328(int, int);

int func_02095380(int a)
{
    int r;
    r = func_02096718(4);
    if (r != 0) {
        return func_0200f328(r, a);
    }
    return r;
}
