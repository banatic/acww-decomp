/* func_ov086_02278a98 @ 0x02278a98, 0x20 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);

int func_ov086_02278a98(void *self)
{
    int ret = 0;

    if (func_02014868((char *) self + 0x618) == 0) {
        ret = 1;
    }
    return ret;
}
