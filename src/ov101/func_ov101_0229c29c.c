/* func_ov101_0229c29c @ 0x0229c29c, 0xe bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229c29c(void *self, int value);

void func_ov101_0229c29c(void *self, int value)
{
    unsigned int *field = (unsigned int *) ((char *) self + 0x94);
    *field |= value;
}
