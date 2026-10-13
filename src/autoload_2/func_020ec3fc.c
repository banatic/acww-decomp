/* func_020ec3fc @ 0x020ec3fc, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern unsigned short data_021fbefc;
extern int func_ov065_0227f208(void);

int func_020ec3fc(void)
{
    if (data_021fbefc <= 1U) {
        return 0;
    }
    return func_ov065_0227f208();
}
