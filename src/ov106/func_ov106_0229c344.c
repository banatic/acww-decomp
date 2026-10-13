/* func_ov106_0229c344 @ 0x0229c344, 0xe bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

void func_ov106_0229c344(void *self, unsigned int mask)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x94);
    *p &= ~mask;
}
