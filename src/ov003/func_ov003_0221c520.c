/* func_ov003_0221c520 @ 0x0221c520, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0221c570(void);
extern int func_ov003_022203dc(void);
extern void func_02064328(void *, void *, int, int);
extern char data_ov003_0223c844[];
extern char data_ov003_02238a8c[];

void *func_ov003_0221c520(void)
{
    int a = func_ov003_0221c570();
    int b = func_ov003_022203dc();
    func_02064328(data_ov003_0223c844, data_ov003_02238a8c, a, b);
    return data_ov003_0223c844;
}
