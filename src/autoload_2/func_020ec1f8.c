/* func_020ec1f8 @ 0x020ec1f8, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_ov066_0226997c(unsigned char);
extern int func_ov065_02277b98(unsigned char);

int func_020ec1f8(void)
{
    unsigned char c = data_021fbef8;
    if ((unsigned char) (c + 0xff) <= 1) {
        return func_ov066_0226997c((unsigned char) (c + 0xff));
    } else if ((unsigned char) (c + 0xfd) <= 1) {
        return (unsigned short) func_ov065_02277b98((unsigned char) (c + 0xfd));
    } else {
        return 1;
    }
}
