/* func_0205f784 @ 0x0205f784, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(void *);
extern void *data_021c9ad0;

void func_0205f784(void **array)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (array[i] != 0) {
            func_020e9b9c(array[i]);
            array[i] = 0;
        }
    }
    if (data_021c9ad0 != 0) {
        func_020e9b9c(data_021c9ad0);
    }
}
