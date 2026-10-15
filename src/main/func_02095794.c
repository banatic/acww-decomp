/* func_02095794 @ 0x02095794, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096718(int);

int func_02095794(int result)
{
    int temp;

    temp = func_02096718(result);
    if (temp != 0) {
        result = temp + 0x6f4;
    } else {
        result = 0;
    }
    return result;
}
