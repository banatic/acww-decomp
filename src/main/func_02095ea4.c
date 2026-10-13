/* func_02095ea4 @ 0x02095ea4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern void func_0200f27c(int, int);

int func_02095ea4(int a, int b)
{
    int result;
    result = func_02096718(b);
    if (result != 0) {
        func_0200f27c(result, a);
        return 1;
    }
    return 0;
}
