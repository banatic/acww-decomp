/* func_02098cc0 @ 0x02098cc0, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098cf8(int, int);
extern int func_02098d14(int, int);

int func_02098cc0(int a, int b, int c)
{
    int diff;
    int val;

    diff = 0x1869f - func_02098cf8(a, 0);
    val = diff >= 0 ? diff : 0;
    if (b == 1) {
        val += func_02098d14(a, c);
    }
    return val;
}
