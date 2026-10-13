/* func_ov050_022629ec @ 0x022629ec, 0x3c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a000(unsigned short *ptr, int count);
extern void func_020154b4(void *a, unsigned short *b, int c, int d, int e);

void func_ov050_022629ec(void *param)
{
    int zero;
    unsigned short arr[2];

    arr[0] = 0x1563;
    if (func_0209a000(arr, 2) == 0) {
        return;
    }
    arr[1] = 0x1563;
    zero = 0;
    func_020154b4(param, &arr[1], 2, 5, zero);
}
