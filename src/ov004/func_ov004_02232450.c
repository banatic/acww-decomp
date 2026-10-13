/* func_ov004_02232450 @ 0x02232450, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67d4(void);
extern int func_020b67ac(void);

int func_ov004_02232450(void)
{
    if (func_020b67d4() != 0 || func_020b67ac() != 0) {
        return 1;
    } else {
        return 0;
    }
}
