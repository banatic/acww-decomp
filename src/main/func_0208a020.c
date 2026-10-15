/* func_0208a020 @ 0x0208a020, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020033c4(void *);

int func_0208a020(void *arg)
{
    void *tested_value0;
    int result;
    if ((tested_value0 = (void *) (*(int *) ((char *) arg + 0x2c))) != 0) {
        result = func_020033c4(tested_value0);
    } else {
        result = 0;
    }
    return result;
}
