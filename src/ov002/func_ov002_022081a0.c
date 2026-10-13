/* func_ov002_022081a0 @ 0x022081a0, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022081a0(void);
extern int func_01ffd41c(void);

int func_ov002_022081a0(void)
{
    int result;
    if (func_01ffd41c() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
