/* func_02098880 @ 0x02098880, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020988a4(int, int);

int func_02098880(int param)
{
    int i;
    int count = 0;
    int j = 0;
    for (i = 0; i < 4; i++) {
        if (func_020988a4(param, i)) {
            count++;
        }
    }
    return count;
}
