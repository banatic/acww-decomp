/* func_02031478 @ 0x02031478, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int, int);

int func_02031478(int arg, int y)
{
    int ret = func_01ffcb2c(arg, y);
    if (ret >= 0x6f && ret <= 0x70) {
        return ret - 0x6f;
    }
    return -1;
}
