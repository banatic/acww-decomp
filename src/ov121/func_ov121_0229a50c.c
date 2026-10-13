/* func_ov121_0229a50c @ 0x0229a50c, 0x16 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int CARD_IsEnabled(void);
extern void func_0203ac2c(void);

void func_ov121_0229a50c(void)
{
    if (CARD_IsEnabled()) {
        func_0203ac2c();
    }
}
