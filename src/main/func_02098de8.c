/* func_02098de8 @ 0x02098de8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098e10(int);
extern int func_02098e64(int);
extern int func_02098e44(int, int);

int func_02098de8(int param)
{
    int r4;
    int r5;
    int result;

    r5 = param;
    r4 = func_02098e10(r5);
    if (func_02098e64(r4) == 1) {
        result = func_02098e44(r5, r4);
    } else {
        result = 0;
    }
    return result;
}
