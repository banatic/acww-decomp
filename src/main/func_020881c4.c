/* func_020881c4 @ 0x020881c4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209f150(const void *, int);

extern unsigned char data_021dc7a8[];

int func_020881c4(unsigned char *param)
{
    if (func_0209f150((const void *) data_021dc7a8, 0x13) == 0 && param[0x236] == 2) {
        return 1;
    }
    return 0;
}
