/* func_ov094_0229b30c @ 0x0229b30c, 0x1a bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_0229b110(int *);

int func_ov094_0229b30c(int *p)
{
    int result;
    if (func_ov094_0229b110(p + 2) != 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}
