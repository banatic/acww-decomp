/* func_02031acc @ 0x02031acc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(void);
extern unsigned char data_020c9085[];

unsigned char func_02031acc(void)
{
    int result;

    result = func_01ffcb2c();
    if (result < 124) {
        return data_020c9085[result * 30];
    } else {
        return 2;
    }
}
