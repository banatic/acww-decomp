/* func_02031acc @ 0x02031acc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int, int);
extern unsigned char data_020c9085[];

unsigned char func_02031acc(int argument0, int argument1)
{
    int result;

    result = func_01ffcb2c((int) argument0, (int) argument1);
    if (result < 124) {
        return data_020c9085[result * 30];
    } else {
        return 2;
    }
}
