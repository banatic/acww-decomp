/* func_ov068_02271358 @ 0x02271358, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02232414(void *);

void func_ov068_02271358(void *p)
{
    short s;
    s = *(short *) ((char *) p + 0x232);
    if (func_ov003_02232414(p)) {
        if (s <= 0) {
            *(char *) ((char *) p + 0x251) = 9;
            *(short *) ((char *) p + 0x242) = 0;
        } else {
            *(short *) ((char *) p + 0x232) = s - 1;
        }
    }
}
