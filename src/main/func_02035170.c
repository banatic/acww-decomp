/* func_02035170 @ 0x02035170, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034f14(void);

void func_02035170(void *arg0)
{
    int val;
    int val2;
    char val3;

    val = func_02034f14();
    if (val >= 0) {
        val2 = *(int *) ((char *) arg0 + 0x1c0);
        if (val < val2) {
            val3 = 1;
            *(char *) ((char *) arg0 + val * 0x1c + 0x13) = val3;
        }
    }
    return;
}
