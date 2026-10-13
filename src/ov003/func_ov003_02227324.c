/* func_ov003_02227324 @ 0x02227324, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064b2c(void *a, void *b, int c, int d);
extern void *func_021077e8(void *a);
extern void func_020560e0(void *a, int b);
extern void *data_021fbe94;

int func_ov003_02227324(void *self, void **dst, void **mid, void **src, int n)
{
    void *h;
    int x, y, z, w;
    int i;
    h = data_021fbe94;
    x = -4;
    y = 0;
    w = 0;
    z = 0;
    for (i = 0; i < n; i++) {
        void *s = *src;
        if (s) {
            *mid = func_02064b2c(s, h, x, y);
            if (*mid == 0) {
                return 0;
            }
            *dst = func_021077e8(*mid);
            func_020560e0(*dst, z);
        } else {
            *dst = (void *) w;
        }
        dst++;
        mid++;
        src++;
    }
    return 1;
}
