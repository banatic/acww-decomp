/* func_ov002_022081a0 @ 0x022081a0, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022081a0(int result);
extern int func_01ffd41c(unsigned char *arg0);

int func_ov002_022081a0(int result)
{
    if (func_01ffd41c((unsigned char *) result) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
