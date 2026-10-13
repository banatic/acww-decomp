/* func_0203e3f8 @ 0x0203e3f8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e4c0(int);
extern unsigned char *data_021c72b8;

int func_0203e3f8(void)
{
    int result;
    unsigned char *ptr;

    if (func_0203e4c0(8) == 0) {
        return 0;
    }

    ptr = data_021c72b8;
    ptr[0x16] = 6;
    return 1;
}
