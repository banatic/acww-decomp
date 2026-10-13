/* func_ov106_0229d48c @ 0x0229d48c, 0x20 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a1e8(int);

int func_ov106_0229d48c(int param)
{
    int r = func_0209a1e8(param);
    if (r == -1) {
        return 0x20;
    } else {
        return (unsigned char) (r + 11);
    }
}
