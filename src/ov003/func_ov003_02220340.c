/* func_ov003_02220340 @ 0x02220340, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220174(unsigned short val);
extern int func_ov009_0226303c(void);

int func_ov003_02220340(unsigned short arg)
{
    if (func_ov003_02220174((unsigned short) (arg + 0x5001)) != 0) {
        return func_ov009_0226303c();
    } else {
        return 0;
    }
}
