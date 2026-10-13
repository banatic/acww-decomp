/* func_02049ff0 @ 0x02049ff0, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204a034(unsigned short *a);

int func_02049ff0(unsigned short *a)
{
    int flag = 0;
    if (func_0204a034(a) != 0) {
        flag = 1;
    } else {
        int r2 = 1;
        int r1 = flag;
        unsigned int val = *a;
        if (val >= 0xe3 && val <= 0xe7) {
            r1 = 1;
        }
        if (r1 == 0) {
            if (val < 0xe8 || val > 0xfb) {
                r2 = 0;
            }
        }
        if (r2 != 0) {
            flag = 1;
        }
    }
    return flag;
}
