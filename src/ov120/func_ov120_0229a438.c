/* func_ov120_0229a438 @ 0x0229a438, 0xe bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov120_0229a438(void *self, unsigned short value);

void func_ov120_0229a438(void *self, unsigned short value)
{
    unsigned short *p = (unsigned short *) ((char *) self + 0x9c);
    *p = (unsigned short) (*p | value);
}
