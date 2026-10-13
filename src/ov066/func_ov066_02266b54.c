/* func_ov066_02266b54 @ 0x02266b54, 0x40 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_02266b94(void);
extern int func_ov066_0226686c(void);
extern int (*data_ov066_0226bdc0[])(int (*)(void));

int func_ov066_02266b54(int idx)
{
    int result;
    result = data_ov066_0226bdc0[idx](func_ov066_02266b94);
    if (result == 2) {
        return result;
    } else {
        return func_ov066_0226686c();
    }
}
