/* func_ov079_02279d00 @ 0x02279d00, 0x20 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void);
extern int func_ov079_02279c34(int, int);

int func_ov079_02279d00(int param)
{
    int result;
    if (func_0202ec58() == 0) {
        result = 0;
    } else {
        func_ov079_02279c34(param, 3);
        result = 1;
    }
    return result;
}
