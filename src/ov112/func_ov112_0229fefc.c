/* func_ov112_0229fefc @ 0x0229fefc, 0x20 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe60(void);
extern int func_ov112_0229ff38(int);
extern int func_ov112_0229ff1c(int);

int func_ov112_0229fefc(int param)
{
    if (func_0206fe60() != 0) {
        return func_ov112_0229ff38(param);
    } else {
        return func_ov112_0229ff1c(param);
    }
}
