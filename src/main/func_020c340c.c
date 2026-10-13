/* func_020c340c @ 0x020c340c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(char *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9,
                         unsigned short arg10, int arg11);
extern unsigned short data_020c80f8;

int func_020c340c(char *param)
{
    func_02019d0c(param + 0x564, 4, 2, 0x10000, 0x1d000, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}
