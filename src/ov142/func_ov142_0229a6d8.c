/* func_ov142_0229a6d8 @ 0x0229a6d8, 0x10 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

short func_ov142_0229a6d8(void *self)
{
    unsigned char idx;
    short result;

    idx = ((unsigned char *) self)[0xbc];
    result = ((short *) ((char *) self + (idx << 1)))[0x62];
    return result;
}
