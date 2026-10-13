/* func_020ec148 @ 0x020ec148, 0x50 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_020ec1b4(void);
extern int func_020ec198(void);
extern unsigned char data_021fbef8;

int func_020ec148(void)
{
    if (data_021fbef8 == 2) {
        return func_020ec1b4();
    }
    if (data_021fbef8 == 4) {
        return func_020ec198();
    }
    return -1;
}
