/* func_ov046_02260720 @ 0x02260720, 0x5c bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1558(void);

void func_ov046_02260720(unsigned char *r5, int r4)
{
    unsigned char *p;
    int t;

    t = 0x10 - func_020b1558();
    r5[0xc5] = (unsigned char) t;
    r5[0xc4] = 0;

    if (r4 == 0) {
        if (func_020b1558() == 0) {
            *(int *) (r5 + 0xdc) = 0x3e;
        } else {
            *(int *) (r5 + 0xdc) = 7;
        }
    } else if (r4 == 1) {
        r5[0xc6] = 2;
        *(int *) (r5 + 0xdc) = 0x1e;
    } else {
        *(int *) (r5 + 0xdc) = 0xc;
    }
}
