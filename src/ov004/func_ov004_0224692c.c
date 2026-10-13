/* func_ov004_0224692c @ 0x0224692c, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov004_0225ff50;
extern void *data_ov004_0225ff54;
extern void func_ov093_02299424(void *p);

void func_ov004_0224692c(void)
{
    if ((data_ov004_0225ff50 & 1) != 0) {
        func_ov093_02299424(data_ov004_0225ff54);
    }
}
