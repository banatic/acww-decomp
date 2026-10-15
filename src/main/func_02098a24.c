/* func_02098a24 @ 0x02098a24, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098cf8(int a, int b);
extern int func_02098adc(int a, int b);
extern void func_02098aa0(int a, int b, int c);

void func_02098a24(int a, int b, int c)
{
    int t;

    t = b + func_02098cf8(a, 0);
    if (t < 0) {
        if (c == 1) {
            t = func_02098adc(a, -t);
            if (t < 0) {
                t = 0;
            } else if ((unsigned) t > 99999) {
                t = 99999;
            }
        } else {
            t = 0;
        }
    }
    func_02098aa0(a, t, c);
}
