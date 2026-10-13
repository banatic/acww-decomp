/* func_ov071_02278aa4 @ 0x02278aa4, 0x20 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);

int func_ov071_02278aa4(void *arg)
{
    int result = 0;
    if (func_02014868((char *) arg + 0x618) == 0) {
        result = 1;
    }
    return result;
}
