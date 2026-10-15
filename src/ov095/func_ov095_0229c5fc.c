/* func_ov095_0229c5fc @ 0x0229c5fc, 0x58 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_022999b0(unsigned int a, unsigned int b);

int func_ov095_0229c5fc(unsigned int a, unsigned int b, unsigned int c)
{
    if (func_ov095_022999b0(a, 4) != 0) {
        if (c < 0x50 || c > 0x58) {
            goto fail;
        }
        if (b < 0x30) {
            return 0x109;
        }
        if (b > 0xd0) {
            return 0x10a;
        }
    } else {
        if (c < 0x48 || c > 0x50) {
            goto fail;
        }
        if (b < 0x30) {
            return 0x109;
        }
        if (b > 0xd0) {
            return 0x10a;
        }
    }
fail:
    return -1;
}
