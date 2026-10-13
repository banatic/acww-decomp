/* func_0204c0b0 @ 0x0204c0b0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c0d8(void *param);
extern int func_0204b42c(void *param);

int func_0204c0b0(void *param)
{
    int result;
    int temp;

    if (func_0204c0d8(param) != 0) {
        temp = func_0204b42c(param);
        result = temp - 0x1188;
    } else {
        result = -1;
    }
    return result;
}
