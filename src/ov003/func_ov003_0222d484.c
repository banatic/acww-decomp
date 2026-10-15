/* func_ov003_0222d484 @ 0x0222d484, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_ov003_0226054c[];
extern char data_ov003_02260bf0[];
extern unsigned char data_ov003_02260538;
extern int func_020ba4e4(void);
extern int func_02046730(void *a);
extern int func_020644cc(int a);

int func_ov003_0222d484(unsigned char *a, unsigned char *b, int c)
{
    int t[4];
    int r = func_020ba4e4();
    if (c != 0) {
        if (r == 0) {
            if (func_02046730(t)) {
                *a = 0x33;
                *b = 8;
                return 1;
            }
            if (data_ov003_0226054c[0] > 0 && func_020644cc(0x64) < 0x14) {
                *a = 0x33;
                *b = 7;
                return 1;
            }
        }
    } else {
        if (r != 1) {
            char *o = data_ov003_02260bf0;
            if (data_ov003_02260538 != 0 && *(unsigned char *) (o + 0x250) == 3 && *(unsigned char *) (o + 0x251) == 0x13) {
                *a = 0x3b;
                *b = 7;
                return 1;
            }
        }
    }
    return 0;
}
