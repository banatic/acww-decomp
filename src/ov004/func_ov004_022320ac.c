/* func_ov004_022320ac @ 0x022320ac, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov004_022589fc;
extern char data_ov004_022589ec[];
extern unsigned short *func_ov004_02232734(void *record);

void *func_ov004_022320ac(void)
{
    char *p = data_ov004_022589fc;
    if (p != 0) {
        return func_ov004_02232734(p + 0x1228);
    }
    return data_ov004_022589ec;
}
