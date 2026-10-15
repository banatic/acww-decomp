/* func_02047fac @ 0x02047fac, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct {
    unsigned char pad[0x30];
    unsigned int : 4;
    signed int bit : 1;
} data_021c79c4;

extern int func_020644cc(int);
extern int func_02048cb8(int a, int b, int c, int d, int e, int (*predicate)(int, int, int), int g);
extern int func_02048e4c(int, int, int);

void func_02047fac(int a, int b, int c)
{
    int tmp;

    if (data_021c79c4.bit) {
        return;
    }
    if (func_020644cc(100) >= 10) {
        return;
    }
    tmp = func_020644cc(c) + 1;
    func_02048cb8(a, b, tmp, 4, 0x1548, (((int (*)(int, int, int)) func_02048e4c)), 0);
}
