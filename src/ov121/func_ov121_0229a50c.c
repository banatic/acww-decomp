/* func_ov121_0229a50c @ 0x0229a50c, 0x16 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int CARD_IsEnabled(void);
extern int func_0203ac2c(void);

int func_ov121_0229a50c(void)
{
    int result = CARD_IsEnabled();
    if (result) {
        result = func_0203ac2c();
    }
    return result;
}
