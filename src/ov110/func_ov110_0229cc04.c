/* func_ov110_0229cc04 @ 0x0229cc04, 0x10 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229d388(void *self, unsigned char byte);

int func_ov110_0229cc04(void *self)
{
    return func_ov110_0229d388(self, ((unsigned char *) self)[0xf5]);
}
