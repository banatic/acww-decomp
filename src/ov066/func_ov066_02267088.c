/* func_ov066_02267088 @ 0x02267088, 0x50 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern int *data_ov066_0226bdec;
extern void func_ov066_02266e64(void);

void func_ov066_02267088(void)
{
    int v;
    v = *data_ov066_0226bdec;
    switch (v) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
            func_ov066_02266e64();
            break;
        case 5:
        default:
            break;
    }
}
