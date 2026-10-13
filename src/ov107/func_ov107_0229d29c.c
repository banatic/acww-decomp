/* func_ov107_0229d29c @ 0x0229d29c, 0x3c bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(char *p, int q);
extern int func_ov107_0229d36c(char *p, int q);
extern int func_ov094_0229aba4(char *p, int q);

int func_ov107_0229d29c(char *param1, int param2)
{
    if (func_ov107_0229d388(param1, param2)) {
        int result = func_ov107_0229d36c(param1, param2);
        return func_ov094_0229aba4(param1 + 0x10c, result);
    } else {
        if (param2 == 0xf) {
            return 0xbc;
        } else {
            return 0;
        }
    }
}
