/* func_020b93e8 @ 0x020b93e8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e948c(void);

extern unsigned char data_021f6c30;
extern unsigned char data_021f6c64;
extern unsigned char data_021f6c40;
extern unsigned char data_021f6c3c;

void func_020b93e8(void)
{
    unsigned char val0;
    unsigned char val1;

    func_020e948c();
    val0 = 0;
    val1 = 0xc8;

    data_021f6c30 = val0;
    data_021f6c64 = val1;
    data_021f6c40 = val0;
    data_021f6c3c = val1;
}
