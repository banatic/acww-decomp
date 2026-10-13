/* func_ov094_0229aa84 @ 0x0229aa84, 0x28 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(int a);
extern int func_02099734(int b);
extern int func_02098e8c(int c, int d);

unsigned char func_ov094_0229aa84(int a, int idx)
{
    if (idx >= 0 && idx <= 14) {
        return (unsigned char) func_02098e8c(func_02099734(func_020984e8(a)), idx);
    }
    return 0;
}
