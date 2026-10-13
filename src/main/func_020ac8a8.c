/* func_020ac8a8 @ 0x020ac8a8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern void func_020e993c(int arg1, int arg2);

void func_020ac8a8(int *param)
{
    if (param[1] != 0) {
        func_020e993c(data_021fbe94, param[1]);
        param[1] = 0;
    }
}
