/* func_02098e44 @ 0x02098e44, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098e64(int param1);

int func_02098e44(int param1, int param2)
{
    int result = 0;
    int temp;

    temp = func_02098e64(param2);
    if (temp == 1) {
        result = param1 + (param2 << 8);
    }
    return result;
}
