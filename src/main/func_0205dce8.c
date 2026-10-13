/* func_0205dce8 @ 0x0205dce8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9af0;
extern void func_020e9b9c(int);

void func_0205dce8(int *arr)
{
    int i;
    int j;
    i = 0;
    j = i;
    do {
        arr[i] = j;
        i++;
    } while (i < 4);
    if (data_021c9af0) {
        func_020e9b9c(data_021c9af0);
    }
}
