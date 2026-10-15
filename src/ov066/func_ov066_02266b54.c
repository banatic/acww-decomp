/* func_ov066_02266b54 @ 0x02266b54, 0x40 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern void func_ov066_02266b94(void *packet);
extern void func_ov066_0226686c(int arg);
extern int (*data_ov066_0226bdc0[])(void (*)(void *));

void func_ov066_02266b54(int idx)
{
    int result;
    result = data_ov066_0226bdc0[idx](func_ov066_02266b94);
    if (result == 2) {
        return;
    } else {
        func_ov066_0226686c(result);
    }
}
