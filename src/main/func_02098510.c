/* func_02098510 @ 0x02098510, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098530(int);

int func_02098510(int x)
{
    int r = -1;
    if (func_02098530(x) == 1) {
        r = x - 4;
    }
    return r;
}
