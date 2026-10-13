/* func_ov071_02279b6c @ 0x02279b6c, 0x2c bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea9e4(void *a, void *b);

int func_ov071_02279b6c(void *self)
{
    if (func_020ea9e4((char *) self + 0x5c, (char *) self + 0x738) > 0xc000) {
        return 0;
    }
    return 1;
}
