/* func_02060c60 @ 0x02060c60, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6818(void);

unsigned char func_02060c60(void)
{
    int ret;
    unsigned char result;

    ret = func_020b6818();
    result = 0;
    if (ret != -1) {
        result = (unsigned char) (1 << ret);
    }
    return result;
}
