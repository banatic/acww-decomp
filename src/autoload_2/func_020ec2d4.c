/* func_020ec2d4 @ 0x020ec2d4, 0x64 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_ov066_0226807c(void);
extern int func_ov065_02277c28(void);

int func_020ec2d4(void)
{
    unsigned char c = data_021fbef8;
    if ((unsigned char) (c + 0xff) <= 1) {
        return func_ov066_0226807c();
    }
    if ((unsigned char) (c + 0xfd) > 1) {
        return 1;
    }
    return func_ov065_02277c28() & 0xff;
}
