/* func_02078b2c @ 0x02078b2c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *data_021c9abc;
extern int func_02085f08(unsigned int **);
extern unsigned int func_020ea0e0(unsigned int, unsigned int *);

void func_02078b2c(unsigned int *arr)
{
    unsigned int *ptr;
    int count;
    int i;
    ptr = data_021c9abc;
    count = func_02085f08(&data_021c9abc);
    for (i = 0; i < count; i++) {
        arr[i] = func_020ea0e0(0x7AC, ptr);
    }
}
