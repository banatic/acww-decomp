/* func_ov004_02232054 @ 0x02232054, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_ov004_022589fc;
extern char data_ov004_022589ec[];
extern void *func_ov004_022329c0(void *p);

void *func_ov004_02232054(void)
{
    char *p = data_ov004_022589fc;
    if (p != 0) {
        return func_ov004_022329c0(p + 0x128);
    }
    return data_ov004_022589ec;
}
