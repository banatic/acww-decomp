/* func_ov134_0229ab80 @ 0x0229ab80, 0x54 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229aaa8(void *, int);
extern int func_ov134_0229aa4c(void *, int);
extern int func_ov134_0229aa78(void *, int);
extern int func_ov134_0229aa3c(void *, int);

int func_ov134_0229ab80(void *p, int a, int b)
{
    int i;
    int r4 = a >> 3;
    int r6 = b >> 3;

    for (i = 0; i <= 2; i++) {
        if (func_ov134_0229aaa8(p, i) > r4) {
            continue;
        }
        if (func_ov134_0229aa4c(p, i) + 3 < r4) {
            continue;
        }
        if (func_ov134_0229aa78(p, i) > r6) {
            continue;
        }
        if (func_ov134_0229aa3c(p, i) < r6) {
            continue;
        }
        return i;
    }
    return 6;
}
