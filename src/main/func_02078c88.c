/* func_02078c88 @ 0x02078c88, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(void *ptr);

extern unsigned char data_021c9ac4[];

void func_02078c88(void *param)
{
    void **global_ptr = *(void ***) data_021c9ac4;
    int i;
    void *ptr;

    for (i = 0; i < 5; i++) {
        ((void **) param)[i] = 0;
    }

    if (global_ptr != 0) {
        func_020e9b9c(global_ptr);
    }
}
