/* func_020ec920 @ 0x020ec920, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_020ecb80(void);
extern int func_020ec980(void);

int func_020ec920(void)
{
    if ((data_021fbef8 == 1) || (data_021fbef8 == 2)) {
        return func_020ecb80();
    }
    if ((data_021fbef8 == 3) || (data_021fbef8 == 4)) {
        return func_020ec980();
    }
    return 0;
}
