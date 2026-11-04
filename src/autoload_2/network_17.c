/* network_17: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020ed3c0 @ 0x020ed3c0, 0x14 bytes, ARM
 * func_020ed370 @ 0x020ed370, 0x50 bytes, ARM
 * func_020ed320 @ 0x020ed320, 0x50 bytes, ARM
 */

extern int data_0213e6bc;
extern int data_0213e6c0;
extern int DWC_Auth_Base64Decode(int p0, int p1, int p2, int p3);
extern int data_021fbf14;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_020ed3c0(void)
{
    data_0213e6bc = 1;
}

void func_020ed370(int p0, int p1, int p2, int p3)
{
    if (p0 != 0 && p1 != 0 && p2 == 0) {
        DWC_Auth_Base64Decode(p0, p1, p3, data_021fbf14);
    }
    data_0213e6c0 = 1;
}

void func_020ed320(const void *a, int b, int c, void *d)
{
    if (a != 0 && b != 0 && c == 0) {
        MI_CpuCopy8(a, d, (*(unsigned int *) &data_021fbf14));
    }
    data_0213e6c0 = 1;
}
