/* func_020ed370 @ 0x020ed370, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ed370(int p0, int p1, int p2, int p3);
extern int data_0213e6c0;
extern int DWC_Auth_Base64Decode(int p0, int p1, int p2, int p3);

extern int data_021fbf14;

void func_020ed370(int p0, int p1, int p2, int p3)
{
    if (p0 != 0 && p1 != 0 && p2 == 0) {
        DWC_Auth_Base64Decode(p0, p1, p3, data_021fbf14);
    }
    data_0213e6c0 = 1;
}
