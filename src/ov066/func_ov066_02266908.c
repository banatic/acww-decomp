/* func_ov066_02266908 @ 0x02266908, 0x48 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int (*data_ov066_0226bde8)(int a, int b);
extern void func_ov066_0226686c(int code);

int func_ov066_02266908(int a, int b)
{
    if (data_ov066_0226bde8) {
        int r = data_ov066_0226bde8(a, b);
        if (r) {
            return r;
        }
    }
    func_ov066_0226686c(0x42);
    return 0;
}
