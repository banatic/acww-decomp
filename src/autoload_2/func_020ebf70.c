/* func_020ebf70 @ 0x020ebf70, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_ov066_02269934(void);
extern int func_020ec040(unsigned int ready);
extern int func_020ebfd8(void);

int func_020ebf70(void)
{
    unsigned char b = data_021fbef8;
    if ((unsigned char) (b + 255) <= 1) {
        return func_020ec040(func_ov066_02269934());
    } else {
        if ((unsigned char) (b + 253) > 1) {
            return 0;
        } else {
            return func_020ec040(func_020ebfd8());
        }
    }
}
