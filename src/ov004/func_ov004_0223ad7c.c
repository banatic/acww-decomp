/* func_ov004_0223ad7c @ 0x0223ad7c, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea0e0(int, void *);
extern void *data_021fbe94;

void func_ov004_0223ad7c(char *self, int a1)
{
    *(int *) (self + 0xa0) = -1;
    *(short *) (self + 0xa4) = -1;
    *(void **) self = func_020ea0e0(0xe00, data_021fbe94);
    *(int *) (self + 4) = a1;
}
