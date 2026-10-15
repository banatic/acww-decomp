/* func_ov076_02279410 @ 0x02279410, 0x3c bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *arg0);
extern void func_ov076_02279370(int, int);

int func_ov076_02279410(int param)
{
    int result;
    int *p;
    short val;

    if (func_0202ec58((void *) param) == 0) {
        return 0;
    }

    p = (int *) (param + 0x4e8);
    *p |= 2;

    val = *(short *) (param + 0x8e);
    *(short *) (param + 0x71e) = val;

    func_ov076_02279370(param, 0);
    return 1;
}
