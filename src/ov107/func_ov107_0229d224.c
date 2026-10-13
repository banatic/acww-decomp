/* func_ov107_0229d224 @ 0x0229d224, 0x3c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d190(void *param, unsigned char i);
extern int func_ov107_0229d36c(void *param, unsigned char i);
extern void func_ov094_0229a888(void *ptr, int value);

void func_ov107_0229d224(void *param)
{
    unsigned char i = 0;
    char *p = (char *) param + 0x10c;
    do {
        if (func_ov107_0229d190(param, i)) {
            func_ov094_0229a888(p, func_ov107_0229d36c(param, i));
        }
        i = (unsigned char) (i + 1);
    } while (i <= 14);
}
