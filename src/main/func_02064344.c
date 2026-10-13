/* func_02064344 @ 0x02064344, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int memcmp(void);

int func_02064344(void)
{
    int result;
    if (memcmp() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
