/* func_02048418 @ 0x02048418, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c79e4[];
extern int func_020644cc(int);
extern int func_02048cb8(int, int, int, int, int, int (*predicate)(int, int, int), int);
extern int func_02048e54(void *, int, int);

void func_02048418(int a, int b, int c, int d)
{
    int v1, v2, i;

    i = 3 - data_021c79e4[0xd];
    v1 = func_020644cc(c - 1);
    v2 = func_020644cc(d - 1);

    while (i > 0) {
        v1 = (v1 + 1 + func_020644cc(c - 1)) % c;
        v2 = (v2 + 1 + func_020644cc(d - 1)) % d;
        func_02048cb8(a, b, v1 + 1, v2 + 1, 0x1549, (((int (*)(int, int, int)) func_02048e54)), 1);
        i--;
    }
}
