/* func_ov066_022670d8 @ 0x022670d8, 0x60 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int *data_ov066_0226bdec;
extern int func_ov066_02266e64(void);
extern int func_ov066_02267be0(void);

int func_ov066_022670d8(void)
{
    int v = *data_ov066_0226bdec;
    switch (v) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
            return func_ov066_02266e64();
        case 5:
            return func_ov066_02267be0();
        case 4:
        default:
            return v;
    }
}
