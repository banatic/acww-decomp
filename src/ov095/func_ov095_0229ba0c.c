/* func_ov095_0229ba0c @ 0x0229ba0c, 0x1c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

int func_ov095_0229ba0c(void *unused, unsigned int key)
{
    if (key >= 0x3131 && key <= 0x314e) {
        return 1;
    }
    return 0;
}
