/* func_ov068_02276394 @ 0x02276394, 0x34 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);

int func_ov068_02276394(void *self)
{
    if (func_02014868((char *) self + 0x618) != 0) {
        return 0;
    }
    if (*(unsigned int *) ((char *) self + 0x898) - 5 <= 1) {
        return 1;
    }
    return 0;
}
