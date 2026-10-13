/* func_ov068_0226ad44 @ 0x0226ad44, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_ov068_0226ad78(int, int, unsigned char, unsigned char, unsigned char);

void func_ov068_0226ad44(int a, int b, unsigned char *arr, int d, unsigned char p5, unsigned char p6)
{
    unsigned char c = arr[func_020644cc(d)];
    if (c == 0) {
        p5 = 0;
    }
    func_ov068_0226ad78(a, b, c, p5, p6);
}
