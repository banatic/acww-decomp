/* func_ov134_0229abd4 @ 0x0229abd4, 0x64 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229aaa8(void *self, int i);
extern int func_ov134_0229aa4c(void *self, int i);
extern int func_ov134_0229aa78(void *self, int i);
extern int func_ov134_0229aa3c(void *self, int i);

int func_ov134_0229abd4(void *self, int a, int b)
{
    int i;
    int x = a >> 3;
    int y = b >> 3;
    for (i = 0; i <= 4; i++) {
        int extra;
        if (i == 3) {
            extra = 2;
        } else {
            extra = 3;
        }
        if (func_ov134_0229aaa8(self, i) > x) {
            continue;
        }
        if (func_ov134_0229aa4c(self, i) + extra < x) {
            continue;
        }
        if (func_ov134_0229aa78(self, i) > y) {
            continue;
        }
        if (func_ov134_0229aa3c(self, i) < y) {
            continue;
        }
        return i;
    }
    return 6;
}
