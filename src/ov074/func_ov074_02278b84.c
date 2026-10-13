/* func_ov074_02278b84 @ 0x02278b84, 0x20 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);

int func_ov074_02278b84(void *arg)
{
    int result;
    int flag = 0;

    if (func_02014868((char *) arg + 0x618) == 0) {
        flag = 1;
    }

    result = flag;
    return result;
}
