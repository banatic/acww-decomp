/* func_ov127_02299680 @ 0x02299680, 0x3c bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1530(int);

int func_ov127_02299680(int param)
{
    int i;
    int j;
    int result;
    int *ptr;

    for (i = 0; i < 16; i++) {
        result = func_020b1530(i);
        if (result != 0) {
            for (j = 0; j < 16; j++) {
                if (param == *(unsigned short *) (result + (j << 1) + 0x2a)) {
                    return i;
                }
            }
        }
    }
    return -1;
}
