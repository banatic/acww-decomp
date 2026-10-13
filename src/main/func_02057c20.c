/* func_02057c20 @ 0x02057c20, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205992c(int a, int b);
extern int data_021c9350;

int func_02057c20(int param)
{
    int result = 0;

    if (data_021c9350) {
        result = func_0205992c(data_021c9350, param);
    }

    return result;
}
