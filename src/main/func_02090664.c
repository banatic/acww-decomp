/* func_02090664 @ 0x02090664, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021d52c8;
extern void func_020e993c(int x, int y);

void func_02090664(int *arr)
{
    int i;
    for (i = 0; i < 3; i++) {
        if (arr[i] != 0) {
            func_020e993c(data_021d52c8, arr[i]);
            arr[i] = 0;
        }
    }
}