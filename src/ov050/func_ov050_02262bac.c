/* func_ov050_02262bac @ 0x02262bac, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a000(void *, int);
extern void func_0209abd0(int);

void func_ov050_02262bac(int *a, int b)
{
    unsigned short local = 0x11a8;
    if (func_0209a000(&local, 0)) {
        func_0209abd0(b);
        a[52] = 3;
    } else {
        a[52] = 1;
    }
}
