/* func_ov140_0229a078 @ 0x0229a078, 0x88 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov140_0229a12c(void *obj);
extern void func_020708e4(void *handle, unsigned short *digits, int size);
extern void func_02070a98(void *handle, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *handle, int a, int b);

void func_ov140_0229a078(unsigned char *obj)
{
    unsigned char *p = obj;
    void *handle = func_ov140_0229a12c(obj);
    unsigned short digits[3];

    if (p[0x8df] < 10) {
        digits[0] = p[0x8df] + 0xff10;
        digits[1] = 0;
        digits[2] = 0;
    } else {
        digits[0] = (p[0x8df] / 10) + 0xff10;
        digits[1] = (p[0x8df] % 10) + 0xff10;
        digits[2] = 0;
    }

    func_020708e4(handle, digits, 3);
    func_02070a98(handle, 8, 0x1f4, 2, 0xf, 0, 1);
    func_02070a04(handle, 0, 0);
}
