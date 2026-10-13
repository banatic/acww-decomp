/* func_ov107_0229d260 @ 0x0229d260, 0x3c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(void *a, int b);
extern int func_ov107_0229d36c(void *a, int b);
extern int func_ov094_0229ab90(void *a, int b);

int func_ov107_0229d260(void *a, int b)
{
    if (func_ov107_0229d388(a, b)) {
        int x = func_ov107_0229d36c(a, b);
        return func_ov094_0229ab90((char *) a + 0x10c, x) - 0x10;
    } else {
        if (b == 15) {
            return 0xb6;
        }
        return 0;
    }
}
