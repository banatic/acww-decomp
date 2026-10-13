/* func_ov066_0226727c @ 0x0226727c, 0x3c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int *data_ov066_0226bdec;
extern int func_ov066_02266b54(int param);

int func_ov066_0226727c(void)
{
    int v = *data_ov066_0226bdec;
    if (v <= 0) {
        return v;
    }
    return func_ov066_02266b54(0);
}
