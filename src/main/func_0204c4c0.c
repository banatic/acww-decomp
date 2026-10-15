/* func_0204c4c0 @ 0x0204c4c0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b1d8(unsigned short *);
extern int func_0204c63c(int param);

int func_0204c4c0(int param)
{
    int result;
    int r4;

    r4 = param;
    if (func_0204b1d8((unsigned short *) param) != 0) {
        if (func_0204c63c(r4) == 8) {
            result = 1;
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    return result;
}
