/* func_ov003_0222da78 @ 0x0222da78, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

extern int data_ov003_02260b98[3];
extern unsigned char data_ov003_02260bd4[];

void func_ov003_0222da78(int *src)
{
    int *d = data_ov003_02260b98;
    data_ov003_02260bd4[9] = 1;
    d[0] = src[0];
    d[1] = src[1];
    d[2] = src[2];
    data_ov003_02260bd4[0x11] = 4;
}
