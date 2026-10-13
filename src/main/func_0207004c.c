/* func_0207004c @ 0x0207004c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02070094(void);
extern unsigned char data_020df328[];

int func_0207004c(int param)
{
    int result;
    if (func_02070094() == 0) {
        result = 0;
    } else {
        data_020df328[1] = (unsigned char) param;
        data_020df328[0] = 2;
        result = 1;
    }
    return result;
}
