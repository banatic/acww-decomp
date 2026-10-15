/* func_ov003_0221c548 @ 0x0221c548, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c868;
extern int data_ov003_02238aa4;
extern int func_ov003_0221c570(void);
extern int func_ov003_022203dc(void);
extern int func_02064328(int *, int *, int, int);

int *func_ov003_0221c548(void)
{
    int a, b;
    a = func_ov003_0221c570();
    b = func_ov003_022203dc();
    func_02064328(&data_ov003_0223c868, &data_ov003_02238aa4, a, b);
    return &data_ov003_0223c868;
}
