/* func_0209727c @ 0x0209727c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02098a0c(void);
extern int func_02097cd4(int, int);

int func_0209727c(int r0, int r1)
{
    int sp;
    int r5;
    int r7;
    int r6;
    int r4;
    int result;

    r5 = r0;
    r7 = r1;
    func_020984e8();
    sp = func_02098a0c();
    r6 = 0;
    r4 = 0;
    while (r4 < r7) {
        if (func_02097cd4(sp, r5) == 0) {
            r6++;
        }
        r5++;
        r4++;
    }
    result = r6;
    return result;
}
