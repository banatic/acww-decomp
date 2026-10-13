/* func_ov004_02246a04 @ 0x02246a04, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov004_0225ff50;
extern void *data_ov004_0225ff54;
extern void func_ov093_02299630(void *p);

void func_ov004_02246a04(void)
{
    if ((data_ov004_0225ff50 & 1) != 0) {
        func_ov093_02299630(data_ov004_0225ff54);
    }
}
