/* func_ov093_02298f8c @ 0x02298f8c, 0x10 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

int func_ov093_02298f8c(unsigned short *ptr, unsigned short mask)
{
    if ((*ptr & mask) != 0) {
        return 1;
    } else {
        return 0;
    }
}
