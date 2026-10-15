/* func_02031a74 @ 0x02031a74, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int, int);
extern unsigned char data_020c9093[];

int func_02031a74(int result, int value)
{

    value = func_01ffcb2c(result, value);
    if (value < 0x7c) {
        result = data_020c9093[value * 30];
    } else {
        result = 0;
    }

    if (result != 0) {
        return 1;
    } else {
        return 0;
    }
}
