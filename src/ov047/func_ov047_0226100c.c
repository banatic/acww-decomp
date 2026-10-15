/* func_ov047_0226100c @ 0x0226100c, 0x20 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014f60(void *self);

void func_ov047_0226100c(void *self)
{
    unsigned short v = *(unsigned short *) ((char *) self + 0xCE);
    if (v != 0xFFF1) {
        func_02014f60(self);
    }
}
