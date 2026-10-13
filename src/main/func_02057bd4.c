/* func_02057bd4 @ 0x02057bd4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *data_021c9350;

int func_02057bd4(void)
{
    int result;
    unsigned char *ptr;
    unsigned char value;

    result = 0;
    ptr = data_021c9350;
    if (ptr != 0) {
        value = ptr[0xc8];
        if (value != 0) {
            result = 1;
        }
    }
    return result;
}
