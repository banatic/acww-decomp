/* func_ov003_02217060 @ 0x02217060, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200fb34(void *self, short value);

int func_ov003_02217060(void *self)
{
    return func_0200fb34(self, *(short *) ((char *) self + 0x7e0));
}
