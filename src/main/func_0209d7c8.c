/* func_0209d7c8 @ 0x0209d7c8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1ad8[];

int func_0209d7c8(int param)
{
    unsigned int i;
    for (i = 0; i < 2; i++) {
        if (param == data_020d1ad8[i * 2]) {
            return 1;
        }
    }
    return 0;
}
