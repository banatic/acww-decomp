/* func_0208b720 @ 0x0208b720, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_02098cf8(int, int);
extern int func_0206f854(void);

int func_0208b720(void)
{
    int a = func_020984e8();
    int result = 0;
    if (a != 0) {
        int b = func_02099734(a);
        int c = func_02098cf8(b, 1);
        int d = func_0206f854();
        result = c + d;
    }
    return result;
}
