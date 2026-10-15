/* func_ov003_022272c0 @ 0x022272c0, 0x64 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064b2c(void *a, void *b, int c, int d);
extern void *func_021077e8(void *a);
extern int func_02056084(void *a, int b);
extern void *data_021fbe94;

int func_ov003_022272c0(void *self, void **dst, void **mid, void **src, int n)
{
    void *h;
    int x, y, z;
    int i;
    h = data_021fbe94;
    x = -4;
    y = 0;
    z = 0;
    for (i = 0; i < n; i++) {
        *mid = func_02064b2c(*src, h, x, y);
        if (*mid == 0) {
            return 0;
        }
        *dst = func_021077e8(*mid);
        func_02056084(*dst, z);
        dst++;
        mid++;
        src++;
    }
    return 1;
}
