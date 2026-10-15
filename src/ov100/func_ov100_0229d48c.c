/* func_ov100_0229d48c @ 0x0229d48c, 0x1a bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov100_0229d620(int a, int b);

int func_ov100_0229d48c(int a, int b)
{
    if (func_ov100_0229d620(a, b) != 0) {
        return (unsigned char) b;
    }
    return 0xF;
}
