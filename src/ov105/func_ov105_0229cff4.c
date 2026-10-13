/* func_ov105_0229cff4 @ 0x0229cff4, 0x48 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d530(void *p, unsigned char c);
extern int func_ov105_0229c340(void *p, int val);

int func_ov105_0229cff4(unsigned char *p)
{
    int r = func_ov105_0229d530(p, p[0x2ba]);
    if (func_ov105_0229c340(p, 0x20) != 0) {
        r += 0x100;
    } else if (func_ov105_0229c340(p, 0x10) != 0) {
        r -= 0x100;
    }
    return r + 8;
}
