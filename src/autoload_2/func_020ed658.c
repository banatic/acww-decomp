/* func_020ed658 @ 0x020ed658, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int (*CTRDGi_WriteAgbFlashSectorAsync)(int, int, int);
extern char data_021fbffa[];

void func_020ed658(int a, int b, int c)
{
    data_021fbffa[a * 4] = 0;
    CTRDGi_WriteAgbFlashSectorAsync(a, b, c);
}
