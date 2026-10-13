/* func_02096398 @ 0x02096398, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020963d4(void *p, int j);

int func_02096398(void *arg)
{
    unsigned int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == func_020963d4(arg, j)) {
                break;
            }
        }
        if (j < 4) {
            continue;
        }
        return i;
    }
    return 4;
}
