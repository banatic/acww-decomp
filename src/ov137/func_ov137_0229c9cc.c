/* func_ov137_0229c9cc @ 0x0229c9cc, 0x40 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_0229a24c(char *p);
extern int func_ov134_0229a8a0(char *p);
extern void func_ov137_0229c978(char *p);

void func_ov137_0229c9cc(char *param)
{
    if (func_ov134_0229a24c(param + 0x2c4) != 0) {
        int ret = func_ov134_0229a8a0(param + 0x2c4);
        if (ret == 6) {
            *(char *) (param + 0x2b77) = 2;
        } else {
            *(char *) (param + 0x2b77) = ret - 1;
        }
        func_ov137_0229c978(param);
    }
}
