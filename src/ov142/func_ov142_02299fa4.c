/* func_ov142_02299fa4 @ 0x02299fa4, 0x18 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov142_02299fbc(int);
extern int func_ov142_0229a07c(int);

int func_ov142_02299fa4(int a)
{
    int res = func_ov142_02299fbc(a);
    if (res != 0) {
        return res;
    }
    return func_ov142_0229a07c(a);
}
