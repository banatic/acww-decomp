/* func_ov003_02220384 @ 0x02220384, 0x1a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220294(void);
extern int func_ov009_0226305c(void);

int func_ov003_02220384(void)
{
    if (func_ov003_02220294()) {
        return func_ov009_0226305c();
    } else {
        return 0;
    }
}
