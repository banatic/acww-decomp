/* func_02057b90 @ 0x02057b90, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205963c(int, int, int);
extern int data_021c9350;

int func_02057b90(int a, int b)
{
    int result = 0;
    if (data_021c9350) {
        result = func_0205963c(data_021c9350, a, b);
    }
    return result;
}
