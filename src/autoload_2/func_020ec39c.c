/* func_020ec39c @ 0x020ec39c, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_020ec434(void);
extern int func_020ec3fc(void);

int func_020ec39c(void)
{
    if ((unsigned char) (data_021fbef8 + 0xff) <= 1) {
        return func_020ec434();
    } else if ((unsigned char) (data_021fbef8 + 0xfd) <= 1) {
        return func_020ec3fc();
    } else {
        return 0;
    }
}
