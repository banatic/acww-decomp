/* func_ov093_022995b0 @ 0x022995b0, 0x80 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov093_02298fac(void *a, int b);
extern int func_020b9bbc(void *a, void *b, int c, int d, int e);
extern void func_ov093_02298f9c(void *a, int b);

void func_ov093_022995b0(void *base)
{
    if (func_ov093_02298fac((char *) base + 0x820, 2) != 0) {
        if (func_020b9bbc((char *) base + 0x24d8, (char *) base + 0x828, 4, 0x800, 0) != 0) {
            func_ov093_02298f9c((char *) base + 0x820, 2);
        }
    }
    if (func_ov093_02298fac((char *) base + 0x18, 2) != 0) {
        if (func_020b9bbc((char *) base + 0x24fc, (char *) base + 0x20, 0, 0x800, 0) != 0) {
            func_ov093_02298f9c((char *) base + 0x18, 2);
        }
    }
}
