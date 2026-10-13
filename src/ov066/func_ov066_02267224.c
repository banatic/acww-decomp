/* func_ov066_02267224 @ 0x02267224, 0x58 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02266b54(int);
extern int *data_ov066_0226bdec;

void func_ov066_02267224(void)
{
    int v = *data_ov066_0226bdec;
    if (v < 1) {
        func_ov066_02266b54(1);
    } else if (v > 1) {
        func_ov066_02266b54(2);
    }
}
