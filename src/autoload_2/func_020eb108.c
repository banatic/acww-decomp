/* func_020eb108 @ 0x020eb108, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc;
extern int data_0213e6c0;
extern int data_021fbf14;
extern void DWC_GetGHTTPData(int, int, int, int);
extern int func_020ed320(void);

int func_020eb108(int a, int b, int c)
{
    if (data_021fbefc < 4) {
        return 0;
    }
    if (data_0213e6c0 == 0) {
        return 0;
    }
    data_021fbf14 = c;
    data_0213e6c0 = 0;
    DWC_GetGHTTPData(a, (int) func_020ed320, b, 0);
    return 1;
}
