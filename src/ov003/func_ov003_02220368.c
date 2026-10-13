/* func_ov003_02220368 @ 0x02220368, 0x1a bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02220294(void);
extern int func_ov009_02262ff8(void);

int func_ov003_02220368(void)
{
    return func_ov003_02220294() ? func_ov009_02262ff8() : 0;
}
