/* func_ov066_02266f78 @ 0x02266f78, 0x60 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern unsigned int *data_ov066_0226bdec;
extern void func_ov066_02266e64(void);
extern void func_ov066_02268d08(void);

void func_ov066_02266f78(void)
{
    unsigned int val = *data_ov066_0226bdec;
    switch (val) {
        case 0:
        case 1:
        case 2:
        case 4:
        case 6:
            func_ov066_02266e64();
            break;
        case 3:
            func_ov066_02268d08();
            break;
        case 5:
        default:
            break;
    }
}
