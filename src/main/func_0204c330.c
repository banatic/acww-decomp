/* func_0204c330 @ 0x0204c330, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204c358(int param);
extern int func_0204b42c(int param);

int func_0204c330(int param)
{
    if (func_0204c358(param) != 0) {
        return func_0204b42c(param) - 0x12b0;
    } else {
        return -1;
    }
}
