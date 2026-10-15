/* func_ov052_02260554 @ 0x02260554, 0x20 bytes, Thumb, module ov052
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov052_02260574(void *arg0);
extern int func_0203e0a8(int, int);

int func_ov052_02260554(int param)
{
    int result;
    if (func_ov052_02260574((void *) param) != 0) {
        func_0203e0a8(param, 0);
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
