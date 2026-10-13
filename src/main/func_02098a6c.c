/* func_02098a6c @ 0x02098a6c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098cc0(int a, int c, int d);
extern int func_02098cf8(int a, int c);

int func_02098a6c(int a, int b, int c, int d)
{
    int result = 0;

    if (b >= 0) {
        int ret = func_02098cc0(a, c, d);
        if (b <= ret) {
            result = 1;
        }
    } else {
        int ret = func_02098cf8(a, c);
        if (-b <= ret) {
            result = 1;
        }
    }

    return result;
}
