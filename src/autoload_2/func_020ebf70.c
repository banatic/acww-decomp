/* func_020ebf70 @ 0x020ebf70, 0x68 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern void func_ov066_02269934(void);
extern int func_020ec040(void);
extern void func_020ebfd8(void);

int func_020ebf70(void)
{
    unsigned char b = data_021fbef8;
    if ((unsigned char) (b + 255) <= 1) {
        func_ov066_02269934();
        return func_020ec040();
    } else {
        if ((unsigned char) (b + 253) > 1) {
            return 0;
        } else {
            func_020ebfd8();
            return func_020ec040();
        }
    }
}
