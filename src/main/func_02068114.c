/* func_02068114 @ 0x02068114, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203d4a8(void);

int func_02068114(void)
{
    int result;
    if (func_0203d4a8() == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
