/* func_020826a8 @ 0x020826a8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf74(void);
extern int func_0208298c(int, int);

extern unsigned char data_021d1d4c[];

int func_020826a8(int arg0)
{
    int result;
    int local_4;

    local_4 = arg0;
    if (func_0207cf74() != 0) {
        result = func_0208298c((unsigned int) data_021d1d4c, local_4);
    } else {
        result = 0;
    }
    return result;
}
