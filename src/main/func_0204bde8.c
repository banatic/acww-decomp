/* func_0204bde8 @ 0x0204bde8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204be10(void);
extern int func_0204b42c(int);

int func_0204bde8(int param)
{
    int result;
    int temp;

    if (func_0204be10() != 0) {
        temp = func_0204b42c(param);
        result = temp - 0x1471;
    } else {
        result = -1;
    }
    return result;
}
