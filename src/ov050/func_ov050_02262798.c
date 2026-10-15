/* func_ov050_02262798 @ 0x02262798, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a000(const unsigned short *p, int n);
extern int func_020154b4(void *dst, const unsigned short *src, int a, int b, int c);

void func_ov050_02262798(void *param, int event)
{
    unsigned short local[2];
    local[0] = 0x1561;
    if (func_0209a000(local, 2)) {
        local[1] = 0x1561;
        func_020154b4(param, &local[1], 0, 5, 0);
    }
}
