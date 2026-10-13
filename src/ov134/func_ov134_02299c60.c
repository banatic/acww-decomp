/* func_ov134_02299c60 @ 0x02299c60, 0x56 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229b884(const char *a, int b);
extern int func_ov134_0229b848(const char *a, int b, const char *c);

int func_ov134_02299c60(const char *param0, int param1, unsigned int param2)
{
    unsigned char i;
    int t;
    for (i = 0; i < param2; i++) {
        t = func_ov134_0229b884(param0, i);
        if (t != func_ov134_0229b848(param0, i, param0 + 0xc8)) {
            return 0;
        }
    }
    if (param1 < func_ov134_0229b848(param0, param2, param0 + 0xc8)) {
        return 1;
    } else {
        return 0;
    }
}
