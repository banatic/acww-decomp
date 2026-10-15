/* func_ov003_0221d5cc @ 0x0221d5cc, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221d64c(void *argument0);
extern int func_02064328(void *, void *, int, int);
extern int data_ov003_0223c914;
extern int data_ov003_022390b8;

int *func_ov003_0221d5cc(void *argument0)
{
    int x = func_ov003_0221d64c(argument0);
    func_02064328(&data_ov003_0223c914, &data_ov003_022390b8, x >> 2, x & 3);
    return &data_ov003_0223c914;
}
