/* func_0207bd48 @ 0x0207bd48, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081f80(short *p);

int func_0207bd48(short *a, int b, int c)
{
    int i = 0;
    int ret = -1;
    for (; i < b; i++) {
        if (func_02081f80(a)) {
            if (c == 0) {
                ret = i;
                break;
            } else {
                c--;
            }
        }
        a++;
    }
    return ret;
}
