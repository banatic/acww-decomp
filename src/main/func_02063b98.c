/* func_02063b98 @ 0x02063b98, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020996ac(int a, int b);
extern int func_0203cdcc(int a, int b);

int func_02063b98(int a, int b)
{
    int result;
    if (a) {
        result = func_0203cdcc(func_020996ac(a, b), b);
    } else {
        result = 0;
    }
    return result;
}
