/* func_ov100_0229d3d8 @ 0x0229d3d8, 0x52 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(int a, int b);
extern int func_ov100_0229d620(int a, int b);
extern int func_ov100_0229d5d4(int a, int b);
extern int func_ov100_0229d60c(int a, int b);
extern int func_ov094_0229ab90(int a, int b);

int func_ov100_0229d3d8(int a, int b)
{
    if (func_ov100_0229d630(a, b) != 0 || func_ov100_0229d620(a, b) != 0) {
        int r = func_ov100_0229d5d4(a, b);
        return func_ov094_0229ab90(a + 0xcc, r);
    } else {
        if (func_ov100_0229d60c(a, b) != 0) {
            if (b == 0x1e) {
                return 0x58;
            } else {
                return 0x68;
            }
        } else {
            return 0;
        }
    }
}
