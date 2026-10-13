/* func_ov002_022087f4 @ 0x022087f4, 0x16 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int FX_MulFunc(int a, int b);

int func_ov002_022087f4(int *self, int arg2)
{
    int value = self[2];
    int ret = FX_MulFunc(value, value);
    return (arg2 * ret) >> 12;
}
