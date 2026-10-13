/* func_ov004_0221fbc4 @ 0x0221fbc4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern void func_02019d0c(int a, int b, int c, int d);

int func_ov004_0221fbc4(int param)
{
    volatile int arr[7];
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] = 0;
    arr[4] = 0;
    arr[5] = data_020c80f8;
    arr[6] = 0;
    func_02019d0c(param + 0x564, 1, 1, 0);
    return 1;
}
