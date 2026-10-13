/* func_0203e110 @ 0x0203e110, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203e4c0(int);

extern unsigned char data_021c72b8[];

int func_0203e110(void)
{
    int result;
    unsigned char *ptr;

    if (func_0203e4c0(4) == 0) {
        if (func_0203e4c0(12) == 0) {
            return 0;
        }
    }
    ptr = *(unsigned char **) data_021c72b8;
    ptr[0x17] = 6;
    return 1;
}
