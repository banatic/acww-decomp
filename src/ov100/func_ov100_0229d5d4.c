/* func_ov100_0229d5d4 @ 0x0229d5d4, 0x36 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d630(int unused0, unsigned int unused1);
extern int func_ov100_0229d620(int, int);
extern int func_ov100_0229d48c(int, int);

int func_ov100_0229d5d4(int a, int b)
{
    if (func_ov100_0229d630(a, b)) {
        return (unsigned char) b;
    }
    if (func_ov100_0229d620(a, b)) {
        return func_ov100_0229d48c(a, b);
    }
    return 0;
}
