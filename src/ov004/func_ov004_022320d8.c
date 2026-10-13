/* func_ov004_022320d8 @ 0x022320d8, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov004_022589fc;
extern char data_ov004_022589ec[];
extern void *func_ov004_02232738(void *p);

void *func_ov004_022320d8(void)
{
    char *p = data_ov004_022589fc;
    if (p != 0) {
        return func_ov004_02232738(p + 0x1228);
    }
    return data_ov004_022589ec;
}
