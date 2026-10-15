/* func_ov009_02264d18 @ 0x02264d18, 0x18 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov009_02264884(void *argument0);

int func_ov009_02264d18(void *argument0)
{
    int *p;
    int result;

    p = (int *) func_ov009_02264884(argument0);
    if (p != 0) {
        result = p[4];
    } else {
        result = 0;
    }
    return result;
}
