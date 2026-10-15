/* func_0204c3a0 @ 0x0204c3a0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c3c8(unsigned short *);
extern int func_0204b42c(int param);

int func_0204c3a0(int param)
{
    int result;
    int temp;

    if (func_0204c3c8((unsigned short *) param) != 0) {
        temp = func_0204b42c(param);
        result = temp - 0x12e8;
    } else {
        result = -1;
    }
    return result;
}
