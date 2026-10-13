/* func_020eae40 @ 0x020eae40, 0x40 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbef8;
extern int data_021fbf34;
extern void func_ov065_0227e67c(void);

int func_020eae40(void)
{
    if (data_021fbef8 == 3) {
        data_021fbf34 = 0;
        func_ov065_0227e67c();
    }
    return 1;
}
