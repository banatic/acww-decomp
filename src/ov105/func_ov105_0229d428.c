/* func_ov105_0229d428 @ 0x0229d428, 0x40 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d76c(int, int);
extern int func_ov105_0229d75c(int, int);
extern int func_ov105_0229d718(int, int);
extern int func_ov094_0229b30c(int, int);

int func_ov105_0229d428(int a, int b)
{
    if (func_ov105_0229d76c(a, b) != 0 || func_ov105_0229d75c(a, b) != 0) {
        int c = func_ov105_0229d718(a, b);
        return func_ov094_0229b30c(a + 0xd5c, c);
    } else {
        return 1;
    }
}
