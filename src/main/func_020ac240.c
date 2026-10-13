/* func_020ac240 @ 0x020ac240, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(int);

int func_020ac240(int param)
{
    int result;
    if (func_0208e4bc(param + 0x20) == 7) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
