/* func_02098aa0 @ 0x02098aa0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098b44(int, unsigned int);

void func_02098aa0(int a, int b, int c)
{
    int value;
    if (b < 0) {
        b = 0;
    }
    if ((unsigned) b > 99999) {
        if (c == 1) {
            int ret = func_02098b44(a, b);
            if ((unsigned) ret <= 99999) {
                value = ret;
            } else {
                value = 99999;
            }
        } else {
            value = 99999;
        }
    } else {
        value = b;
    }
    *(int *) ((char *) a + 0xa68) = value;
}
