/* func_020ec1b4 @ 0x020ec1b4, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_0226760c(void);
extern int func_ov066_022677e0(int);

int func_020ec1b4(void)
{
    if (func_ov066_0226760c() != 7) {
        return -1;
    } else {
        return func_ov066_022677e0(0);
    }
}
