/* func_ov004_0220fed0 @ 0x0220fed0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099870(void);
extern int func_02094ffc(void);
int func_ov004_0220fed0(void)
{
    if (func_020984e8() != 0 && func_02099870() != 0) {
        if (func_02094ffc() == 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
