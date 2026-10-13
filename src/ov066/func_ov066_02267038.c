/* func_ov066_02267038 @ 0x02267038, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov066_02266e64(void);
extern int *data_ov066_0226bdec;

void func_ov066_02267038(void)
{
    int x = *data_ov066_0226bdec;
    switch (x) {
        case 0:
        case 1:
        case 2:
            func_ov066_02266e64();
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        default:
            break;
    }
}
