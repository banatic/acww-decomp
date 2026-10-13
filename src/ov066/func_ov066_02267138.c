/* func_ov066_02267138 @ 0x02267138, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern int *data_ov066_0226bdec;
extern void func_ov066_02266e64(void);

void func_ov066_02267138(void)
{
    int v = *data_ov066_0226bdec;
    switch (v) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
            func_ov066_02266e64();
            break;
        default:
            break;
    }
}
