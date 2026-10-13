/* func_02098e74 @ 0x02098e74, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02098e8c(void);

int func_02098e74(void)
{
    int result;
    if (func_02098e8c() == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
