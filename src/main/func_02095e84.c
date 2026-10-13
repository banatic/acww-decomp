/* func_02095e84 @ 0x02095e84, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);
extern void func_0200f268(int, int);

int func_02095e84(int a, int b)
{
    int ret;
    if ((ret = func_02096718(b))) {
        func_0200f268(ret, a);
        return 1;
    }
    return 0;
}
