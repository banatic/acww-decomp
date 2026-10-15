/* func_ov003_0221a888 @ 0x0221a888, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221a8ac(void *argument0);

int func_ov003_0221a888(int *this)
{
    int result;
    int tmp;

    if (func_ov003_0221a8ac(this) != 0) {
        tmp = this[2] - 2;
        if ((tmp & 1) != 0) {
            result = 0;
        } else {
            result = 1;
        }
    } else {
        result = 0;
    }
    return result;
}
