/* func_ov003_0221c4f8 @ 0x0221c4f8, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221c570(void);
extern int func_ov003_022203dc(void);
extern int func_02064328(void *p1, void *p2, int n, int m);
extern int data_ov003_0223c88c;
extern int data_ov003_02238a74;

void *func_ov003_0221c4f8(void)
{
    int n = func_ov003_0221c570();
    int m = func_ov003_022203dc();

    func_02064328(&data_ov003_0223c88c, &data_ov003_02238a74, n, m);

    return &data_ov003_0223c88c;
}
