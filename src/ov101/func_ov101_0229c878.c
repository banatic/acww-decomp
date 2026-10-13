/* func_ov101_0229c878 @ 0x0229c878, 0x44 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229cd08(void *p, unsigned char b);
extern int func_ov101_0229c2ac(void *p, int v);

int func_ov101_0229c878(void *p)
{
    int r = func_ov101_0229cd08(p, *(unsigned char *) ((char *) p + 0xb3));
    if (func_ov101_0229c2ac(p, 0x10)) {
        r += 0x100;
    } else if (func_ov101_0229c2ac(p, 8)) {
        r -= 0x100;
    }
    return r + 8;
}
