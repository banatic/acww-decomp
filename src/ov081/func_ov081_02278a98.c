/* func_ov081_02278a98 @ 0x02278a98, 0x20 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(const void *ptr);

int func_ov081_02278a98(char *ptr)
{
    int ret = 0;
    if (func_02014868(ptr + 0x618) == 0) {
        ret = 1;
    }
    return ret;
}
