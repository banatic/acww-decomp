/* func_020eb108 @ 0x020eb108, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc;
extern int data_0213e6c0;
extern int data_021fbf14;
extern int DWC_GetGHTTPData(const char *url, void (*completed)(const void *, int, int, void *), void *argument);
extern void func_020ed320(const void *buffer, int length, int result, void *argument);

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
    DWC_GetGHTTPData((const char *) a, func_020ed320, (void *) b);
    return 1;
}
