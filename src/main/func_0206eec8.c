/* func_0206eec8 @ 0x0206eec8, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021cfc20;
extern unsigned short data_021cfc18;
extern int (*data_020df2a4[])(void);
extern void func_0200284c(int, int, int);

void func_0206eec8(void)
{
    if (data_020df2a4[data_021cfc20]() == 0) {
        return;
    }
    data_021cfc18 = (data_021cfc18 + 1) & 0x1ff;
    if (data_021cfc20 == 2 || data_021cfc20 == 4 || (unsigned short) (data_021cfc20 + 0xfff6) <= 1) {
        func_0200284c(1, data_021cfc18, data_021cfc18);
    } else {
        func_0200284c(5, data_021cfc18, data_021cfc18);
    }
}
