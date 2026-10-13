/* func_ov070_02278a98 @ 0x02278a98, 0x20 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);

int func_ov070_02278a98(void *arg)
{
    int result = 0;
    if (func_02014868((char *) arg + 0x618) == 0) {
        result = 1;
    }
    return result;
}
