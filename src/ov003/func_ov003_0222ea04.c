/* func_ov003_0222ea04 @ 0x0222ea04, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0222e98c(void *a, int b);
extern int func_0203adc4(void *a, int b, int c);
extern void func_ov003_0222e2d8(void *a, void *b);

int func_ov003_0222ea04(void *ctx, char *o, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        if (*(unsigned char *) (o + 0x250) == 3 && *(unsigned char *) (o + 0x249) != 0) {
            if (n == 8) {
                if (func_ov003_0222e98c(ctx, *(unsigned char *) (o + 0x24d)) == 0 ||
                    func_0203adc4(o + 0x204, 0x2000, 0x2000) == 0) {
                    func_ov003_0222e2d8(ctx, o);
                }
            } else {
                func_ov003_0222e2d8(ctx, o);
            }
        }
        o += 0x25c;
    }
    return 1;
}
