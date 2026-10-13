/* func_0203fae4 @ 0x0203fae4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a12e8(void);
extern int func_020984e8(void);
extern int func_02099020(int, int);

int func_0203fae4(void)
{
    int ret = 0;
    int r;
    if (func_020a12e8()) {
        ret = 1;
    } else {
        r = func_020984e8();
        if (r == 0 || func_02099020(r, 1)) {
            ret = 1;
        }
    }
    return ret;
}
