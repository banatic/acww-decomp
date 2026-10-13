/* func_0203e234 @ 0x0203e234, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e4c0(void);
extern unsigned char *data_021c72b8;

int func_0203e234(void)
{
    int result;
    unsigned char *ptr;

    if (func_0203e4c0() == 0) {
        result = 0;
    } else {
        ptr = data_021c72b8;
        ptr[0x16] = 6;
        result = 1;
    }
    return result;
}
