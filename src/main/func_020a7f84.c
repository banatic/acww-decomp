/* func_020a7f84 @ 0x020a7f84, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7dcc(void);
extern unsigned short data_021fbe40[];

int func_020a7f84(void)
{
    int result = 0;
    if (func_020a7dcc() == 0) {
        result = (data_021fbe40[1] & 0x40) ? 1 : 0;
    }
    return result;
}
