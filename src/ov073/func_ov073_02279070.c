/* func_ov073_02279070 @ 0x02279070, 0x50 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern volatile unsigned short data_020c80f8;
extern void func_02019d0c(char *p, int a, int b, int c);
extern void func_02013c04(char *p);

int func_ov073_02279070(char *r4)
{
    volatile int arr[7];
    arr[0] = 0;
    arr[1] = 0;
    arr[2] = 0;
    arr[3] = 0;
    arr[4] = 0;
    arr[5] = data_020c80f8;
    arr[6] = 0;
    func_02019d0c(r4 + 0x564, 0, 1, 0);
    *(r4 + 0x651) = 0;
    func_02013c04(r4 + 0x558);
    return 1;
}
