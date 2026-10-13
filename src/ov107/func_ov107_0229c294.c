/* func_ov107_0229c294 @ 0x0229c294, 0xe bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov107_0229c294(void *self, unsigned int mask);

void func_ov107_0229c294(void *self, unsigned int mask)
{
    unsigned int *p = (unsigned int *) ((char *) self + 0x94);
    *p &= ~mask;
}
