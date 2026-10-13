/* func_0207a650 @ 0x0207a650, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209dd9c(void *a, void *b);
extern int func_0209dcdc(void *a, void *b);

int func_0207a650(void *param0, void *param1)
{
    int ret = 1;
    unsigned char *base = (unsigned char *) param0;
    if (base[0x404F] != 0) {
        if (func_0209dd9c(param1, base + 0x404C) != 0) {
            if (func_0209dcdc(param1, base + 0x404C) < 14) {
                ret = 0;
            }
        } else {
            if (func_0209dcdc(base + 0x404C, param1) < 14) {
                ret = 0;
            }
        }
    }
    return ret;
}
