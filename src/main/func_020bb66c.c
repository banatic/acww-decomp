/* func_020bb66c @ 0x020bb66c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e6070[];
extern int data_021fbe94;
extern int func_02002c4c(int, int, int, int, int, int);

int func_020bb66c(int a, int index, int c)
{
    int result = 0;
    if (func_02002c4c(data_020e6070[index], data_021fbe94, c, 16, 16, 47) != 0) {
        result = 1;
    }
    return result;
}
