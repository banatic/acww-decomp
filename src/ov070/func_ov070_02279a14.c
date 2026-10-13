/* func_ov070_02279a14 @ 0x02279a14, 0x3c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void);
extern int func_ov070_02279974(int, int);

int func_ov070_02279a14(int param)
{
    int result;
    int *ptr;
    char *byte_ptr;

    if (func_0202ec58() == 0) {
        return 0;
    }

    func_ov070_02279974(param, 0);

    ptr = (int *) ((char *) param + 0x4e8);
    *ptr |= 2;

    byte_ptr = (char *) param + 0x738;
    *byte_ptr = 0;

    return 1;
}
