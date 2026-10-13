/* func_020ecfec @ 0x020ecfec, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int data_021fbf34;
extern void DWC_SetMatchingOption(int, int *);

void func_020ecfec(void)
{
    unsigned char val = data_021fbef8;
    data_021fbf34 = 0;
    if (val != 3) {
        return;
    }
    {
        int x = 1;
        DWC_SetMatchingOption(1, &x);
    }
}
