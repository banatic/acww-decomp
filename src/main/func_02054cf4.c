/* func_02054cf4 @ 0x02054cf4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcc10(int p1, int p2);
extern int func_02054d14(int p1, int p2);

int func_02054cf4(int p1, int p2)
{
    int ret;
    ret = func_01ffcc10(p1, p2);
    if (ret == 0) {
        return func_02054d14(p1, p2);
    }
    return ret;
}
