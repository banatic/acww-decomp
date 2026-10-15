/* func_ov003_0221c314 @ 0x0221c314, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(unsigned int *a);
extern void MI_CpuCopy8(unsigned int *src, unsigned int *dst, unsigned int size);
extern int func_0203fc78(int a, unsigned int *b, int c);
extern void *func_020b65c4(void);
extern int func_02084cd0(const void *a, void *b, void *c);
extern char data_ov003_02238784[];

int func_ov003_0221c314(void *param)
{
    unsigned int a[2];
    unsigned int b[2];
    int flag;

    a[0] = 0;
    a[1] = 0;
    func_0209e474(a);
    MI_CpuCopy8(a, b, 8);
    flag = func_0203fc78(0x40, b, 0) != 0;
    if (flag) {
        func_02084cd0(data_ov003_02238784, func_020b65c4(), (char *) param + 0x5c);
    }
    return 1;
}
