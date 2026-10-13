/* func_ov106_0229d4e4 @ 0x0229d4e4, 0x32 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov106_0229d390(void *a, int b, int c);
extern int func_ov106_0229d48c(void *a);
extern void func_ov106_0229d518(void *a, int b, int c);

void func_ov106_0229d4e4(void *a, int b, int c)
{
    int v = 0x20;
    if (c >= 0xc0) {
        if (func_ov106_0229d390(a, b, c)) {
            v = func_ov106_0229d48c(a);
        }
    }
    if (v != 0x20) {
        b = v;
    }
    func_ov106_0229d518(a, b, 4);
}
