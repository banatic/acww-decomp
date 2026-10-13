/* func_020ead58 @ 0x020ead58, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int WXC_GetStateCode(void);

int func_020ead58(void)
{
    int result;
    result = WXC_GetStateCode();
    if (result == 2) {
        return 1;
    } else {
        return 0;
    }
}
