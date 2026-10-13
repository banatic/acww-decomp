/* func_ov004_022469dc @ 0x022469dc, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov004_0225ff50;
extern void *data_ov004_0225ff54;
extern void func_ov093_022995b0(void *p);

void func_ov004_022469dc(void)
{
    if ((data_ov004_0225ff50 & 1) != 0) {
        func_ov093_022995b0(data_ov004_0225ff54);
    }
}
