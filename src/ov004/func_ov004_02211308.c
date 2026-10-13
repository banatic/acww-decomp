/* func_ov004_02211308 @ 0x02211308, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0221132c(char *self);
extern int func_ov004_0220d2b8(char *p);
int func_ov004_02211308(char *self)
{
    int r;
    if (func_ov004_0221132c(self)) {
        r = func_ov004_0220d2b8(self + 0x740);
    } else {
        r = 0;
    }
    return r;
}
