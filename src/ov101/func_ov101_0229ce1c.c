/* func_ov101_0229ce1c @ 0x0229ce1c, 0x1a bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov101_0229ce38(int);

int func_ov101_0229ce1c(int a1, int a2)
{
    int r4;
    int result;

    r4 = a2;
    if (func_ov101_0229ce38(a1) != 0) {
        result = (unsigned char) r4;
    } else {
        result = 0;
    }
    return result;
}
