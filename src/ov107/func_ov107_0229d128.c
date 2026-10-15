/* func_ov107_0229d128 @ 0x0229d128, 0x34 bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov107_0229d388(unsigned int object, unsigned int index);
extern int func_ov107_0229d36c(char *, int);
extern int func_ov094_0229a69c(char *, int);

int func_ov107_0229d128(char *param0, int param1)
{
    if (func_ov107_0229d388((unsigned int) param0, (unsigned int) param1)) {
        return func_ov094_0229a69c(param0 + 0x10c, func_ov107_0229d36c(param0, param1));
    } else {
        return 1;
    }
}
