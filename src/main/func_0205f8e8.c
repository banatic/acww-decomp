/* func_0205f8e8 @ 0x0205f8e8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c9ae0;
extern void func_020e9b9c(void *p);

void func_0205f8e8(int *arr)
{
    int i;
    for (i = 0; i < 4; i++) {
        arr[i] = 0;
    }
    if (data_021c9ae0) {
        func_020e9b9c(data_021c9ae0);
    }
}
