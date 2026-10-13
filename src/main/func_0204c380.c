/* func_0204c380 @ 0x0204c380, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c3c8(void);
extern int func_0204c3a0(int);
extern int func_0204fd54(int);

int func_0204c380(int param)
{
    int r4;
    int result;

    r4 = param;
    if (func_0204c3c8() != 0) {
        result = func_0204fd54(func_0204c3a0(r4));
    } else {
        result = 10;
    }
    return result;
}
