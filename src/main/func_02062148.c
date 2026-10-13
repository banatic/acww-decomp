/* func_02062148 @ 0x02062148, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cb5c0;
extern unsigned short data_021cb5b0;
extern int func_0206266c(unsigned short *p);
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);

unsigned int func_02062148(unsigned short *target)
{
    int count;
    unsigned short cur;
    int falseVal1;
    int falseVal2;

    if (data_021cb5c0 == 0) {
        goto notfound;
    }

    count = 0;
    cur = data_021cb5b0;
    falseVal1 = 0;
    falseVal2 = 0;

    while (cur < 0x156e) {
        unsigned short tmp = cur;
        int matched;

        if (func_0206266c(&tmp) != 0) {
            if (func_0204bcdc(&tmp) != 0) {
                matched = (func_0204bc64(&tmp) == func_0204bc64(target)) ? 1 : falseVal1;
            } else {
                matched = (tmp == *target) ? 1 : falseVal2;
            }

            if (matched != 0) {
                return count;
            }
            count++;
        }

        cur = (unsigned short) (cur + 1);
    }

notfound:
    return 0xFFFFFFFF;
}
