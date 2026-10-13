/* func_020ecb80 @ 0x020ecb80, 0x28 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ecb80(void);
extern int func_ov066_0226760c(void);

int func_020ecb80(void)
{
    int result;
    result = func_ov066_0226760c();
    if ((unsigned int) (result - 10) <= 1) {
        return 1;
    } else {
        return 0;
    }
}
