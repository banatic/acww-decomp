/* func_020ec260 @ 0x020ec260, 0x74 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned char data_021fbef8;
extern int func_ov066_022699cc(void) __attribute__((arm));
extern int DWC_GetMyAID(void) __attribute__((thumb));

int func_020ec260(void)
{
    unsigned char b = data_021fbef8;
    if ((unsigned char) (b + 0xFF) <= 1) {
        if (b == 1) {
            return 0;
        }
        return func_ov066_022699cc();
    } else {
        if ((unsigned char) (b + 0xFD) <= 1) {
            return DWC_GetMyAID();
        } else {
            return 0;
        }
    }
}
