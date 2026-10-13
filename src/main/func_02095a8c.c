/* func_02095a8c @ 0x02095a8c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern int func_020095b0(int, int, int, int);

int func_02095a8c(int a, int b)
{
    int x;
    x = func_02096718(b);
    if (x != 0) {
        return func_020095b0(x, a, 5, -1);
    } else {
        return 0;
    }
}
