/* func_ov054_02261dc0 @ 0x02261dc0, 0x1c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f8c8(void);
extern unsigned char func_ov054_02261da4(void *receiver);

int func_ov054_02261dc0(int param)
{
    if (func_0206f8c8() != 0) {
        return 0x58;
    }
    return func_ov054_02261da4((void *) param);
}
