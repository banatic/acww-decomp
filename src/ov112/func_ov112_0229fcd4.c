/* func_ov112_0229fcd4 @ 0x0229fcd4, 0x4a bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov112_0229f900(void *p);
extern void func_ov112_0229fc48(void *p, int a1, int a2, unsigned char min, int diff);

void func_ov112_0229fcd4(void *p)
{
    unsigned char b0, b1, min;
    int diff;
    int a1, a2;

    if (func_ov112_0229f900(p)) {
        b1 = ((unsigned char *) p)[0xbf];
        b0 = ((unsigned char *) p)[0xbe];
        if (b0 > b1) {
            min = b1;
            diff = b0 - b1;
        } else {
            min = b0;
            diff = b1 - b0;
        }
        a1 = 13;
        a2 = 14;
    } else {
        diff = 0;
    }

    if (diff != 0) {
        func_ov112_0229fc48(p, a1, a2, min, diff);
    }
}
