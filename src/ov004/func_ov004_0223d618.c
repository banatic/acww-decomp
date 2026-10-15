/* func_ov004_0223d618 @ 0x0223d618, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b67d4(void);
extern int func_ov004_0223e2f0(char *self);
int func_ov004_0223d618(char *self)
{
    if (func_020b67d4() != 0) {
        return func_ov004_0223e2f0(self);
    }
    return 1;
}
