/* func_ov134_0229aad8 @ 0x0229aad8, 0x54 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229aaa8(int, int);
extern int func_ov134_0229aa4c(int, int);
extern int func_ov134_0229aa78(int, int);
extern int func_ov134_0229aa3c(int, int);

int func_ov134_0229aad8(int a, int b, int c)
{
    int i;
    int r4 = b >> 3;
    int r6 = c >> 3;

    for (i = 3; i <= 4; i++) {
        if (func_ov134_0229aaa8(a, i) > r4) {
            continue;
        }
        if (func_ov134_0229aa4c(a, i) + 3 < r4) {
            continue;
        }
        if (func_ov134_0229aa78(a, i) > r6) {
            continue;
        }
        if (func_ov134_0229aa3c(a, i) < r6) {
            continue;
        }
        return i;
    }
    return 6;
}
